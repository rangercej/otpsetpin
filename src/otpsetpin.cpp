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


#include "utils.h"
#include "options.h"

using namespace std;

const string ErrNoPin = "NOPIN";

const int RcOkay = 0;
const int RcError = 1;
	
Options options;
Utils utils(options);

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
		throw err.str();
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
	vector<string> args = utils.mkArgs(argc, argv);

	string user;
	try {
		if (args.size() > 1) {
			user = utils.getUser(args[1]);
		} else {
			user = utils.getCurrentUser();
		}
	
		if (utils.validateUserPin(user)) {
			throw "Invalid PIN.";
		}
	
		string newpin1 = utils.getPassword("Enter new PIN");
		string newpin2 = utils.getPassword("Enter new PIN again");
	
		if (newpin1 != newpin2) {
			throw "PINs do not match.";
		}
	
		savePin(user, newpin2);
		
		return RcOkay;
	}
	catch (const char *msg) {
		cerr << msg << endl;
	}
	catch (string msg) {
		cerr << msg << endl;
	}

	return RcError;
}
