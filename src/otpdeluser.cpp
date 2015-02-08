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

extern "C" {
	#include <unistd.h>
	#include <liboath/oath.h>
}

#include "utils.h"
#include "options.h"

Options options;

//----------------------------------------------------------------------------
// Summary: Program entry point
// Params:
//     argc - Count of command line parameters
//     argv - Command line parameters
// Returns: program exit code
int main(int argc, char **argv)
{
	if (argc == 0) {
		std::cout << "Syntax: otpdeluser {user}" << std::endl;
		return 1;
	}

	std::vector<std::string> args = Utils::mkArgs(argc, argv);

	std::string deluser(argv[1]);

	if (deluser == "") {
		std::cout << "No user provided." << std::endl;
		return 1;
	}

	try {
		UserInfo userinfo(deluser, options);
		userinfo.Delete();
	}
	catch (const char* msg)
	{
		std::cerr << "ERROR: " << msg << std::endl;
	}
	catch (std::string msg)
	{
		std::cerr << "ERROR: " << msg << std::endl;
	}

	return 0;
}
