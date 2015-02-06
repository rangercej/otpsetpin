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
// Summary: Get a password/PIN from the terminal
// Params:
//     prompt - The prompt to display to the user
// Returns: User entered password.
string getPassword(string prompt)
{
	prompt.append(": ");
	return getpass(prompt.c_str());
}

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
// Summary: Convert the secret to a hex string
// Params: Secret to convert
// Returns: Hex version of the secret
string toHex(char *secret)
{
	char hexBuffer[1024];
	oath_bin2hex(secret, SECRETLENGTH, hexBuffer);

	return string(hexBuffer);
}

//----------------------------------------------------------------------------
// Summary: Convert the secret to a base32 string
// Params: Secret to convert as a hex string
// Returns: Base32 version of the secret
string toBase32(char *secret)
{
	char *b32Buffer;
	size_t b32Length;
	oath_base32_encode(secret, SECRETLENGTH, &b32Buffer, &b32Length);

	string b32Secret(b32Buffer);
	::free(b32Buffer);

	return b32Secret;
}

//----------------------------------------------------------------------------
// Summary: Add the user for OTP auth
// Params:
//     user   - User that we're adding/updating
//     newpin - PIN for the user
//     secret - Shared secret for the user
// Returns: nothing
void savePin (string user, string newpin, string secret)
{
	string tempFile = options.DefaultAuthFile + ".new";
	string type;
	string userin;
	string pin, temp;
	bool userwrote = false;
	
	{
		ifstream authFile(options.DefaultAuthFile.c_str());
		ofstream newAuthFile(tempFile.c_str());

		if (newAuthFile.fail()) {
			throw "Failed to open auth file.";
		}

		while (authFile >> type >> userin >> temp)
		{
			if (userin != user) {
				newAuthFile << type << " " << userin << " " << temp << endl;
			} else {
				newAuthFile << type << " " << user << " " << newpin << " " << secret << endl;
				userwrote = true;
			}
		}

		if (!userwrote) {
			newAuthFile << "HOTP/T30 " << user << " " << newpin << " " << secret << endl;
		}
	}

	int val = ::rename(tempFile.c_str(), options.DefaultAuthFile.c_str());
	if (val != 0) {
		ostringstream errtxt;
		errtxt << "Failed to update auth file: " << options.DefaultAuthFile;
		throw errtxt.str();
	}
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

	vector<string> args = mkArgs(argc, argv);

	string newuser(argv[1]);

	if (newuser == "") {
		cout << "No user provided.";
		return 1;
	}

	ostringstream prompt;
	prompt << "Enter PIN for new user " << newuser;
	string password = getPassword(prompt.str());

	try {
		char secretbytes[64];
		getSecret(secretbytes);
		string secret = toHex(secretbytes);
		savePin(newuser, password, secret);

		// See https://code.google.com/p/google-authenticator/wiki/KeyUriFormat for URL format
		cout << "User added. URL for QR is:";
		cout << "otpauth://totp/" << newuser << "@" << getHostName() << "?secret=" << toBase32(secretbytes) << endl;
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
