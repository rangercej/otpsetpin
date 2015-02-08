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

#ifndef __OTP_OPTIONS_H_
#define __OTP_OPTIONS_H_

#include <string>
#include <vector>

class Options
{
	private:
		std::string ConfigFile;
		std::string DefaultAuthFile;
		std::string Issuer;
		int Digits;

		bool IsInitialized;

		void SetDefaults();

		static std::vector<std::string> split(const std::string &s, char delim);
		static void split(const std::string &s, char delim, std::vector<std::string> & target);

		static std::string & rtrim(std::string &s);
		static std::string & ltrim(std::string &s);
		static std::string & trim(std::string &s);
	public:
		Options();
		Options(const std::string & configFile);

		void ReadOptions();
		std::string GetConfigFile() const;
		std::string GetAuthFile() const;
		std::string GetIssuer() const;
		int GetDigits() const;
};

#endif
