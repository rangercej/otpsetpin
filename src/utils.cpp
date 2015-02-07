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

#include <vector>
#include <fstream>
#include <sstream>

#include "options.h"
#include "utils.h"
#include "userinfo.h"

extern "C" {
	#include <unistd.h>
	#include <pwd.h>
}

using namespace std;

//----------------------------------------------------------------------------
//
Utils::Utils(const Options & opts)
{
	options = opts;
}

//----------------------------------------------------------------------------
// Summary: Create a vector from the command line arguments
// Returns: Vector of argv
vector<string> Utils::mkArgs (int argc, char **argv)
{
	vector<string> args;

	for (int i = 0; i < argc; i++) {
		args.push_back(argv[i]);
	}

	return args;
}

//----------------------------------------------------------------------------
// Summary: Get a password/PIN from the terminal
// Params:
//     prompt - The prompt to display to the user
// Returns: User entered password.
string Utils::getPassword(string prompt)
{
	prompt.append(": ");
	return getpass(prompt.c_str());
}

//----------------------------------------------------------------------------
// Summary: Validate user PIN
// Params:
//	user - User whose PIN to fetch and validate against current PIN
// Returns: true on success
bool Utils::validateUserPin(UserInfo & userinfo)
{
	ostringstream prompt;
	prompt << "Enter existing PIN for " << userinfo.UserId;
	string password = getPassword(prompt.str());

	if (password != userinfo.PinNumber) {
		return false;
	}

	return true;
}

//----------------------------------------------------------------------------
// Summary: user in system authentication database (/etc/passwd)
// Returns: true or false
bool Utils::isUserKnownToSystem(string username)
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
string Utils::getUser(string user)
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
string Utils::getCurrentUser()
{
	int uid = geteuid();

	struct passwd *userData = getpwuid(uid);
	if (userData == NULL) {
		throw "Could not determine current user";
	}

	return string(userData->pw_name);
}
