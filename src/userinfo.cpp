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
#include <sstream>
#include <fstream>
#include <iostream>

#include "userinfo.h"
#include "utils.h"
#include "options.h"

using namespace std;

UserInfo::UserInfo(string userId, Options & options)
{
	OtpOptions = options;
	AuthFileName = options.DefaultAuthFile;
	UserId = userId;
	Mode = "";
	PinNumber = "";
	Secret = "";
	Get();
}

//----------------------------------------------------------------------------
// Summary: Fetch user details from the auth file
// Params: none
// Returns: nothing
void UserInfo::Get()
{
	string type;
	string userin;
	string pin, secret, temp;
	
	ifstream authFile(AuthFileName.c_str());
	if (authFile.fail())
	{
		throw "Cannot open authorisation file.";
	}

	while (authFile >> type >> userin >> pin >> secret && getline(authFile, temp)) {
		if (userin == UserId) {
			Mode = type;
			PinNumber = pin;
			Secret = secret;
		}
	}

}

//----------------------------------------------------------------------------
// Summary: Update the user details in the auth file
// Params: none
// Returns: nothing
void UserInfo::Update()
{
	string type;
	string userin;
	string pin, secret, temp;
	bool userwrote = false;
	string tempFile = AuthFileName + ".new";
	
	{
		ifstream authFile(AuthFileName.c_str());
		ofstream newAuthFile(tempFile.c_str());
		while (authFile >> type >> userin >> pin >> secret && getline(authFile, temp)) {
			if (userin != UserId) {
				newAuthFile << type << " " << userin << " " << pin << " " << secret << " " << temp << endl;
			} else {
				newAuthFile << Mode << " " << UserId << " " << PinNumber << " " << Secret << " " << temp << endl;
				userwrote = true;
			}
		}
	}	

	if (!userwrote) {
		// We should never call this, but have it in just in case
		// something happens (a race possibly?).
		stringstream err;
		err << "Error - didn't update user " << UserId << ". User removed from OTP?";
		throw err.str();
	} else {
		::rename(tempFile.c_str(), AuthFileName.c_str());
	}
}

//----------------------------------------------------------------------------
// Summary: Create or update the user details in the auth file
// Params: none
// Returns: nothing
void UserInfo::Create()
{
	string type;
	string userin;
	string pin, secret, temp;
	bool userwrote = false;
	string tempFile = AuthFileName + ".new";
	
	{
		ifstream authFile(AuthFileName.c_str());
		ofstream newAuthFile(tempFile.c_str());
		while (authFile >> type >> userin >> pin >> secret && getline(authFile, temp))
		{
			if (userin != UserId) {
				newAuthFile << type << " " << userin << " " << pin << " " << secret << " " << temp << endl;
			} else {
				newAuthFile << Mode << " " << UserId << " " << PinNumber << " " << Secret << " " << temp << endl;
				userwrote = true;
			}
		}

		if (!userwrote) {
			newAuthFile << Mode << " " << UserId << " " << PinNumber << " " << Secret << " " << endl;
		}
	}	

	::rename(tempFile.c_str(), AuthFileName.c_str());
}

string UserInfo::GetUrl()
{
	stringstream url;
	url << "otppath://totp/" << OtpOptions.Issuer << ":" << UserId << "?secret=" << Utils::hexToBase32(Secret) << "&digits=" << OtpOptions.Digits;

	return url.str();
}
