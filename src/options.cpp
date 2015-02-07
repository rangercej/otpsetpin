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

#include "options.h"

#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iostream>

#include <cstdlib>

using namespace std;

Options::Options()
{
	SetDefaults();
	ReadOptions();
}

Options::Options(string configFile)
{
	SetDefaults();
	ConfigFile = configFile;
	ReadOptions();
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
	ifstream configFile(ConfigFile.c_str());
	string line;

	if (configFile.fail()) {
		cout << "Warning: could not find configuration file, using defaults" << endl;
		return;
	}

	while (getline(configFile, line)) {
		line = trim(line);
		if (line.size() == 0) {
			continue;
		}
		if (line.substr(0, 1) == "#") {
			continue;
		}

		vector<string> parts = split(line, '=');
		string property = trim(parts[0]);
		string value = trim(parts[1]);
		if (property == "otplength") {
			int val = atoi(trim(value).c_str());
			if (val != 6 || val != 8) {
				throw "'otplength' must either be 6 or 8";
			}
			Digits = val;
		} else if (property == "issuer") {
			Issuer = value;
		} else if (property == "authfile") {
			DefaultAuthFile = value;
		} else {
			throw "Unknown configuration directive";
		}
	}
}

vector<string> Options::split(const string &s, char delim)
{
	vector<string> elems;
	split (s, delim, elems);
	return elems;
}

void Options::split(const string &s, char delim, vector<string> & target)
{
	stringstream ss(s);
	string item;
	while (getline(ss, item, delim)) {
		target.push_back(item);
	}
}

inline string & Options::ltrim(string &s)
{
	s.erase(s.begin(), find_if(s.begin(), s.end(), not1(ptr_fun<int, int>(isspace))));
	return s;
}

inline string & Options::rtrim(string &s)
{
	s.erase(find_if(s.rbegin(), s.rend(), not1(ptr_fun<int, int>(isspace))).base(), s.end());
	return s;
}

inline string & Options::trim(string &s)
{
	return ltrim(rtrim(s));
}
