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

#ifndef __OTP_UTILS_H_
#define __OTP_UTILS_H_

#include <vector>
#include "options.h"
#include "userinfo.h"

#define SECRETLENGTH	32

class Utils
{
	public:
		Utils();

		static bool runningAsRoot();
		static std::vector<std::string> mkArgs (int argc, char **argv);
		static std::string getPassword(const std::string & prompt);
		static bool validateUserPin(const UserInfo & user);
		static bool isUserKnownToSystem(const std::string & username);
		static std::string getUser(const std::string & user);
		static std::string getCurrentUser();
		static std::string getHostName();

		static std::string toHex(const char *bytes);
		static std::string toBase32(const char *bytes);
		static std::string hexToBase32(const std::string & hexString);
};

#endif
