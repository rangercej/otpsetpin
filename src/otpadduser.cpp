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
#include <iomanip>
#include <iterator>
#include <algorithm>

#include <unistd.h>
#include <stdlib.h>

extern "C" {
#include <liboath/oath.h>
}

#include "utils.h"
#include "options.h"

using namespace std;

Options options;

//----------------------------------------------------------------------------
// Summary: Get the computer name
// Params: none
// Returns: computer name, or UNKNOWN on error
string getHostName()
{
	char hostBuffer[256];
	int result = gethostname(hostBuffer, sizeof(hostBuffer));
	if (result == -1) {
		return "[UNKNOWN]";
	} else {
		return hostBuffer;
	}
}

//----------------------------------------------------------------------------
// Summary: Get a secret for a user
// Params: none
// Returns: The secret to use
void getSecret(char *target)
{
	char *p = (char*)target;
	fstream randomStream("/dev/urandom");
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
	if (argc == 0) {
		cout << "Syntax: otpadduser {user}" << endl;
		return 1;
	}

	vector<string> args = Utils::mkArgs(argc, argv);

	string newuser(argv[1]);

	if (newuser == "") {
		cout << "No user provided.";
		return 1;
	}

	ostringstream prompt;
	prompt << "Enter PIN for new user " << newuser;
	string password = Utils::getPassword(prompt.str());

	try {
		char secretbytes[64];
		getSecret(secretbytes);
		string secret = Utils::toHex(secretbytes);

		UserInfo userinfo(newuser, options.DefaultAuthFile);
		userinfo.Mode = "HOTP/T30";
		userinfo.PinNumber = password;
		userinfo.Secret = secret;
		userinfo.Create();

		// See https://code.google.com/p/google-authenticator/wiki/KeyUriFormat for URL format
		cout << "User added. URL for QR is:" << endl;
		cout << userinfo.GetUrl();
		//cout << "otpauth://totp/otpsetpin:" << newuser << "@" << getHostName() << "?secret=" << toBase32(secretbytes) << endl;
	}
	catch (const char* msg)
	{
		cerr << "ERROR: " << msg << endl;
	}
	catch (string msg)
	{
		cerr << "ERROR: " << msg << endl;
	}

	return 0;
}
