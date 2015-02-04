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

#include <unistd.h>
#include <stdlib.h>

#include "utils.h"

using namespace std;

const string DefaultFile = "/home/chris/users.auth";
const string DefaultNewFile = "/home/chris/users.auth.new";
const string ErrNoPin = "NOPIN";

enum ReturnCodes {
	RcOkay = 0,
	RcErrNoUser,
	RcErrNoOtp,
	RcErrPinMismatch,
	RcErrBadPin,
	RcErrFileError
};
	

//----------------------------------------------------------------------------
// Summary: Get the current login
// Returns: current login ID
string getUserName()
{
	char username[64] = {0};
	int namelen = getlogin_r(username, sizeof(username) - 1);

	if (namelen == 0) {
		return username;
	} else {
		return "";
	}
}

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
// Summary: Fetch a user's current PIN from the authorisation file
// Params:
//     user - The prompt to display to the user
// Returns: PIN in the auth file, or empty string if user is not yet listed
string getCurrentPin (string user)
{
	ifstream authFile(DefaultFile.c_str());
	string type;
	string userin;
	string pin, temp;
	
	while (authFile >> type >> userin >> pin >> temp)
	{
		if (userin == user) {
			if (pin.compare("-") == 0) {
				return "";
			} else {
				return pin;
			}

			break;
		}
	}

	return ErrNoPin;
}

//----------------------------------------------------------------------------
// Summary: Update the PIN for the user in the auth file (or add the user if
//	the login doesn't already exist
// Params:
//     user   - User that we're adding/updating
//     newpin - PIN for the user
// Returns: nothing
void savePin (string user, string newpin)
{
	ifstream authFile(DefaultFile.c_str());
	ofstream newAuthFile(DefaultNewFile.c_str());
	string type;
	string userin;
	string pin, temp;
	bool userwrote = false;
	
	while (authFile >> type >> userin >> pin >> temp)
	{
		if (userin != user) {
			newAuthFile << type << " " << userin << " " << pin << " " << temp << endl;
		} else {
			newAuthFile << type << " " << user << " " << newpin << " " << temp << endl;
			userwrote = true;
		}
	}

	if (!userwrote) {
		// We should never call this, but have it in just in case
		// something happens (a race possibly?).
		cerr << "Error - didn't update user " << user << ". User removed from OTP?" << endl;
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
	vector<string> args = mkArgs(argc, argv);

	string user = getUserName();
	if (user == "") {
		cout << "Could not get current username.";
		return RcErrNoUser;
	}

	string currentPin = getCurrentPin(user);
	if (currentPin == ErrNoPin) {
		cout << "User not configured for OTP.";
		return RcErrNoOtp;
	}

	ostringstream prompt;
	prompt << "Enter existing PIN for " << user;
	string password = getPassword(prompt.str());

	if (password != currentPin) {
		cout << "Invalid PIN." << endl;
		return RcErrBadPin;
	}

	string newpin1 = getPassword("Enter new PIN");
	string newpin2 = getPassword("Enter new PIN again");

	if (newpin1 != newpin2) {
		cout << "PINs do not match";
		return RcErrPinMismatch;
	}

	savePin(user, newpin2);
	::rename(DefaultNewFile.c_str(), DefaultFile.c_str());
	
	return RcOkay;
}
