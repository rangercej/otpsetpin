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

#include <cstdlib>

extern "C" {
	#include <unistd.h>
	#include <pwd.h>
	#include "liboath/oath.h"
}

#include "utils.h"
#include "userinfo.h"
#include "otperror.h"

//----------------------------------------------------------------------------
Utils::Utils()
{
}

//----------------------------------------------------------------------------
// Summary: Create a vector from the command line arguments
// Returns: Vector of argv
std::vector<std::string> Utils::mkArgs (int argc, char **argv)
{
	std::vector<std::string> args;

	for (int i = 0; i < argc; i++) {
		args.push_back(argv[i]);
	}

	return args;
}

//----------------------------------------------------------------------------
// Summary: Is the effective UID root?
// Params: none
// Returns: true if running as root.
bool Utils::runningAsRoot()
{
	return 0 == getuid();
}

//----------------------------------------------------------------------------
// Summary: Get a password/PIN from the terminal
// Params:
//     prompt - The prompt to display to the user
// Returns: User entered password.
std::string Utils::getPassword(const std::string & prompt)
{
	std::string s = prompt;
	s.append(": ");
	return getpass(s.c_str());
}

//----------------------------------------------------------------------------
// Summary: Validate user PIN
// Params:
//	user - User whose PIN to fetch and validate against current PIN
// Returns: true on success
bool Utils::validateUserPin(const UserInfo & userinfo)
{
	std::ostringstream prompt;
	prompt << "Enter existing PIN for " << userinfo.GetUserId();
	std::string password = getPassword(prompt.str());

	if (password != userinfo.GetPinNumber()) {
		return false;
	}

	return true;
}

//----------------------------------------------------------------------------
// Summary: user in system authentication database (/etc/passwd)
// Returns: true or false
bool Utils::isUserKnownToSystem(const std::string & username)
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
std::string Utils::getUser(const std::string & user)
{
	int uid = getuid();
	if (uid != 0) {
		throw OtpError(OtpError::ErrorCodes::PermissionDenied);
	}

	if (!isUserKnownToSystem(user)) {
		throw OtpError(OtpError::ErrorCodes::UnknownUser, user);
	}

	return user;
}

//----------------------------------------------------------------------------
// Summary: Get the current login
// Returns: current login ID
std::string Utils::getCurrentUser()
{
	int uid = getuid();

	struct passwd *userData = getpwuid(uid);
	if (userData == NULL) {
		throw OtpError(OtpError::ErrorCodes::CannotDetermineUser);
	}

	return std::string(userData->pw_name);
}

//----------------------------------------------------------------------------
// Summary: Get the computer name
// Params: none
// Returns: computer name, or UNKNOWN on error
std::string Utils::getHostName()
{
	char hostBuffer[256];
	int result = gethostname(hostBuffer, sizeof(hostBuffer));
	if (result == -1) {
		return "[UNKNOWN]";
	} else {
		return hostBuffer;
	}
}
