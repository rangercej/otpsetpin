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

#include <unistd.h>
#include <stdlib.h>

using namespace std;

const string DefaultFile = "/home/chris/users.auth";
const string DefaultNewFile = "/home/chris/users.auth.new";

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
// Summary: Get a secret for a user
// Params: none
// Returns: The secret to use
string getSecret()
{
	return "";
}

//----------------------------------------------------------------------------
// Summary: Convert the secret to a base32 string
// Params: Secret to convert as a hex string
// Returns: Base32 version of the secret
string toBase32(string secret)
{
	return "";
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
	ifstream authFile(DefaultFile.c_str());
	ofstream newAuthFile(DefaultNewFile.c_str());
	string type;
	string userin;
	string pin, temp;
	bool userwrote = false;
	
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

	string newuser(argv[1]);

	if (newuser == "") {
		cout << "No user provided."
		return 1;
	}

	ostringstream prompt;
	prompt << "Enter PIN for new user " << user;
	string password = getPassword(prompt.str());
	string secret = getSecret();

	savePin(user, password, secret);
	::rename(DefaultNewFile.c_str(), DefaultFile.c_str());
	
	// See https://code.google.com/p/google-authenticator/wiki/KeyUriFormat for URL format
	cout << "User added. URL for QR is:"
	cout << "otpauth://totp/" << user << "@host" << "?secret=" << toBase32(secret);

	return 0;
}
