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
#include <vector>

#include <cstdlib>

#include "utils.h"
#include "options.h"
#include "userinfo.h"

const int RcOkay = 0;
const int RcError = 1;
	
Options options;

//----------------------------------------------------------------------------
// Summary: Program entry point
// Params:
//     argc - Count of command line parameters
//     argv - Command line parameters
// Returns: program exit code
int main(int argc, char **argv)
{
	std::vector<std::string> args = Utils::mkArgs(argc, argv);

	std::string user;
	try {
		if (args.size() > 1) {
			user = Utils::getUser(args[1]);
		} else {
			user = Utils::getCurrentUser();
		}
	
		UserInfo userinfo(user, options);

		if (!Utils::runningAsRoot()) {
			if (!Utils::validateUserPin(userinfo)) {
				throw "Invalid PIN.";
			}
		}
	
		std::string newpin1 = Utils::getPassword("Enter new PIN");
		std::string newpin2 = Utils::getPassword("Enter new PIN again");
	
		if (newpin1 != newpin2) {
			throw "PINs do not match.";
		}
	
		userinfo.SetPinNumber(newpin2);
		userinfo.Update();
		
		return RcOkay;
	}
	catch (const char *msg) {
		std::cerr << msg << std::endl;
	}
	catch (std::string msg) {
		std::cerr << msg << std::endl;
	}

	return RcError;
}
