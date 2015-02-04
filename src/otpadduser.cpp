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
vector<unsigned short> getSecret()
{
	char b;
	fstream randomStream("/dev/urandom");
	vector<unsigned short> data;

	for (int i = 0; i < 20; i++)
	{
		randomStream.read(&b, 1);
		data.push_back((unsigned char)b);
	}

	return data;
}

//----------------------------------------------------------------------------
// Summary: Convert the secret to a hex string
// Params: Secret to convert
// Returns: Hex version of the secret
string toHex(vector<unsigned short> data)
{
	ostringstream hexString;

	hexString << hex << setfill('0');
	for (vector<unsigned short>::iterator it = data.begin(); it != data.end(); ++it) {
		unsigned short x = *it;
		hexString << setw(2) << x;
		cout << x << ": " << hexString.str() << endl;
	}

	return hexString.str();
}

//----------------------------------------------------------------------------
// Summary: Convert the secret to a base32 string
// Params: Secret to convert as a hex string
// Returns: Base32 version of the secret
string toBase32(vector<unsigned short> data)
{
	const char *b32charset = "ABCDEFGHIJKLMNOPQRSTUVWXYZ234567";
	unsigned long long value;
	ostringstream b32String;

	for (unsigned short i = 0; i < data.size(); i+=5)
	{
		value = data[i] + data[i+1]*16 + data[i+2]*256 + data[i+3]*4096 + data[i+4]*65536;
		for (unsigned long long val = value; val != 0 ; val = val >> 5)
		{
			int j = val & 31;
			b32String << b32charset[j];
		}
	}

	return b32String.str();
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
		cout << "No user provided.";
		return 1;
	}

	ostringstream prompt;
	prompt << "Enter PIN for new user " << newuser;
	string password = getPassword(prompt.str());

	vector<unsigned short> secretbytes = getSecret();
	string secret = toHex(secretbytes);
	savePin(newuser, password, secret);
	::rename(DefaultNewFile.c_str(), DefaultFile.c_str());

cout << secret << endl;
	
	// See https://code.google.com/p/google-authenticator/wiki/KeyUriFormat for URL format
	cout << "User added. URL for QR is:";
	cout << "otpauth://totp/" << newuser << "@host" << "?secret=" << toBase32(secretbytes) << endl;

	return 0;
}
