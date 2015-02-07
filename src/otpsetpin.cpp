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
#include <cpwd>
#include <sys/ctypes>

#include <unistd.h>

#include "utils.h"
#include "options.h"

using namespace std;

const string ErrNoPin = "NOPIN";

enum ReturnCodes {
	RcOkay = 0,
	RcErr,
	RcErrNoOtp,
	RcErrPinMismatch,
	RcErrBadPin,
	RcErrFileError
};
	
Options options;

//----------------------------------------------------------------------------
// Summary: user in system authentication database (/etc/passwd)
// Returns: true or false
string isUserKnownToSystem(string username)
{
	if (username == "") {
		return false;
	}

	if(getpwnam(username.c_str()) == NULL) {
		return false;
	} else {
		return true;
	} 
}

//----------------------------------------------------------------------------
// Summary: get and validate a user-supplied user ID
// Returns: passed in username
string getUser(string user)
{
	int euid = geteuid();
	if (euid != 0) {
		throw "Cannot change another user's PIN";
	}

	if (!isUserKnownToSystem(user)) {
		stringstream err;
		err << "User not known: " << user;
		throw err.str();
	}

	return user;
}

//----------------------------------------------------------------------------
// Summary: Get the current login
// Returns: current login ID
string getCurrentUser()
{
	char username[64] = {0};
	int namelen = getlogin_r(username, sizeof(username) - 1);

	if (namelen != 0) {
		throw "Could not determine current user";
	}

	return username;
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
// Returns: PIN in the auth file
string getCurrentPin (string user)
{
	ifstream authFile(options.DefaultAuthFile.c_str());
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

	throw "User not configured for OTP";
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
	string type;
	string userin;
	string pin, temp;
	bool userwrote = false;
	string tempFile = options.DefaultAuthFile + ".new";
	
	{
		ifstream authFile(options.DefaultAuthFile.c_str());
		ofstream newAuthFile(tempFile.c_str());
		while (authFile >> type >> userin >> pin >> temp)
		{
			if (userin != user) {
				newAuthFile << type << " " << userin << " " << pin << " " << temp << endl;
			} else {
				newAuthFile << type << " " << user << " " << newpin << " " << temp << endl;
				userwrote = true;
			}
		}
	}	

	if (!userwrote) {
		// We should never call this, but have it in just in case
		// something happens (a race possibly?).
		stringstream err;
		err << "Error - didn't update user " << user << ". User removed from OTP?";
		throw err;
	} else {
		::rename(tempFile.c_str(), options.DefaultAuthFile.c_str());
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

	string user;
	try {
		if (args.length > 0) {
			user = getUser(args[0]);
		} else {
			user = getCurrentUser();
		}
	
		string user = getUserName();
		string currentPin = getCurrentPin(user);

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
		
		return RcOkay;
	}
	catch (const char *msg) {
		cerr << msg;
	}
	catch (stringstream msg) {
		cerr << msg.str();
	}
}
