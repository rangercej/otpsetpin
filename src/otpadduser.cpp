/*****************************************************************************
Copyright (c) 2015 C Johnson <cej@nightwolf.org.uk>

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
*****************************************************************************/

#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>

#include <cstdlib>

extern "C" {
	#include <unistd.h>
	#include <liboath/oath.h>
}

#include "utils.h"
#include "options.h"
#include "otperror.h"

Options options;

//----------------------------------------------------------------------------
// Summary: Get a secret for a user
// Params: none
// Returns: The secret to use
void getSecret(char *target)
{
	char *p = (char*)target;
	std::fstream randomStream("/dev/urandom");
	randomStream.read(p, SECRETLENGTH);
}

//----------------------------------------------------------------------------
// Summary: Program entry point
// Params:
//     argc - Count of command line parameters
//     argv - Command line parameters
// Returns: program exit code
int main(int argc, char **argv)
{
	if (argc == 1) {
		std::cout << "Syntax: otpadduser {user}" << std::endl;
		return 1;
	}

	std::vector<std::string> args = Utils::mkArgs(argc, argv);

	std::string newuser(argv[1]);

	if (newuser == "") {
		std::cout << "No user provided." << std::endl;
		return 1;
	}

	std::ostringstream prompt;
	prompt << "Enter PIN for new user " << newuser;
	std::string password = Utils::getPassword(prompt.str());

	try {
		char secretbytes[64];
		getSecret(secretbytes);
		std::string secret = Utils::toHex(secretbytes);

		UserInfo userinfo(newuser, options);
		userinfo.SetMode("HOTP/T30").SetPinNumber(password).SetSecret(secret);
		userinfo.Create();

		// See https://code.google.com/p/google-authenticator/wiki/KeyUriFormat for URL format
		std::cout << "User added. URL for QR is:" << std::endl;
		std::cout << userinfo.GetUrl() << std::endl;
	}
	catch (OtpError err)
	{
		std::cerr << "ERROR: " << err.GetMessage() << std::endl;
		return err.GetErrorCode();
	}

	return 0;
}
