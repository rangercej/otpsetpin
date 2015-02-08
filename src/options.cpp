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

#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iostream>

#include <cstdlib>

#include "options.h"
#include "otperror.h"

Options::Options()
{
	SetDefaults();
	IsInitialized = false;
}

Options::Options(const std::string & configFile)
{
	SetDefaults();
	ConfigFile = configFile;
	IsInitialized = false;
}

void Options::SetDefaults()
{
	DefaultAuthFile = "/etc/users.oath";
	ConfigFile = "/etc/options.oath";
	Digits = 6;
	Issuer = "OtpSetPin";
}

void Options::ReadOptions()
{
	std::ifstream configFile(ConfigFile.c_str());
	std::string line;

	if (configFile.fail()) {
		std::cout << "Warning: could not find configuration file, using defaults" << std::endl;
		return;
	}

	while (std::getline(configFile, line)) {
		line = trim(line);
		if (line.size() == 0) {
			continue;
		}
		if (line.substr(0, 1) == "#") {
			continue;
		}

		std::vector<std::string> parts = split(line, '=');
		std::string property = trim(parts[0]);
		std::string value = trim(parts[1]);
		if (property == "otplength") {
			int val = atoi(trim(value).c_str());
			if (val != 6 && val != 8) {
				throw OtpError(OtpError::ErrorCodes::ConfBadOtpLength);
			}
			Digits = val;
		} else if (property == "issuer") {
			Issuer = value;
		} else if (property == "authfile") {
			DefaultAuthFile = value;
		} else {
			throw OtpError(OtpError::ErrorCodes::ConfUnknownDirective);
		}
	}

	IsInitialized = true;
}

std::vector<std::string> Options::split(const std::string &s, char delim)
{
	std::vector<std::string> elems;
	split (s, delim, elems);
	return elems;
}

void Options::split(const std::string &s, char delim, std::vector<std::string> & target)
{
	std::stringstream ss(s);
	std::string item;
	while (std::getline(ss, item, delim)) {
		target.push_back(item);
	}
}

inline std::string & Options::ltrim(std::string &s)
{
	s.erase(s.begin(), std::find_if(s.begin(), s.end(), std::not1(std::ptr_fun<int, int>(std::isspace))));
	return s;
}

inline std::string & Options::rtrim(std::string &s)
{
	s.erase(std::find_if(s.rbegin(), s.rend(), std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
	return s;
}

inline std::string & Options::trim(std::string &s)
{
	return ltrim(rtrim(s));
}

std::string Options::GetConfigFile() const
{
	if (!IsInitialized) {
		throw OtpError(OtpError::ErrorCodes::ConfNotInit);
	}

	return ConfigFile;
}

std::string Options::GetAuthFile() const
{
	if (!IsInitialized) {
		throw OtpError(OtpError::ErrorCodes::ConfNotInit);
	}

	return DefaultAuthFile;
}

std::string Options::GetIssuer() const
{
	if (!IsInitialized) {
		throw OtpError(OtpError::ErrorCodes::ConfNotInit);
	}

	return Issuer;
}

int Options::GetDigits() const
{
	if (!IsInitialized) {
		throw OtpError(OtpError::ErrorCodes::ConfNotInit);
	}

	return Digits;
}
