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
#include "otperror.h"

UserInfo::UserInfo(const std::string & userId, const Options & options)
{
	OtpOptions = options;
	AuthFileName = options.GetAuthFile();
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
	std::string type;
	std::string userin;
	std::string pin, secret, temp;
	
	std::ifstream authFile(AuthFileName.c_str());
	if (authFile.fail())
	{
		throw OtpError(OtpError::ErrorCodes::AuthFileReadError);
	}

	while (authFile >> type >> userin >> pin >> secret && std::getline(authFile, temp)) {
		if (userin == UserId) {
			Mode = type;
			PinNumber = pin;
			Secret = secret;
		}
	}

}

//----------------------------------------------------------------------------
// Summary: Delete the user details from the auth file
// Params: none
// Returns: nothing
void UserInfo::Delete()
{
	UpdateUserFile(UserAction::Delete);
}

//----------------------------------------------------------------------------
// Summary: Update the user details in the auth file
// Params: none
// Returns: nothing
void UserInfo::Update()
{
	UpdateUserFile(UserAction::Update);
}

//----------------------------------------------------------------------------
// Summary: Create or update the user details in the auth file
// Params: none
// Returns: nothing
void UserInfo::Create()
{
	UpdateUserFile(UserAction::Create);
}

//----------------------------------------------------------------------------
// Summary: Manage writing to the auth file
// Params: How to write the user
// Returns: nothing
void UserInfo::UpdateUserFile(int userAction)
{
	std::string type;
	std::string userin;
	std::string pin, secret, temp;
	bool userwrote = false;
	std::string tempFile = AuthFileName + ".new";
	
	{
		std::ifstream authFile(AuthFileName.c_str());
		std::ofstream newAuthFile(tempFile.c_str());
		if (newAuthFile.fail()) {
			throw OtpError(OtpError::ErrorCodes::AuthFileWriteError);
		}

		while (authFile >> type >> userin >> pin >> secret && std::getline(authFile, temp)) {
			if (userin != UserId) {
				newAuthFile << type << " " << userin << " " << pin << " " << secret << " " << temp << std::endl;
			} else {
				userwrote = true;
				if (userAction != UserAction::Delete) {
					newAuthFile << Mode << " " << UserId << " " << PinNumber << " " << Secret << " " << temp << std::endl;
				}
			}
		}

		if (!userwrote && userAction == UserAction::Create) {
			newAuthFile << Mode << " " << UserId << " " << PinNumber << " " << Secret << " " << std::endl;
			userwrote = true;
		}
	}	

	if (!userwrote) {
		throw OtpError(OtpError::ErrorCodes::UserWriteError, UserId);
	} else {
		::rename(tempFile.c_str(), AuthFileName.c_str());
	}
}

//----------------------------------------------------------------------------
// Summary: Create OTP URL for use with QR code for FreeOTP
// Params: none
// Returns: otppath:// URL string
std::string UserInfo::GetUrl() const
{
	std::stringstream url;
	url << "otppath://totp/" << OtpOptions.GetIssuer() << ":" << UserId << "@" << Utils::getHostName() << "?secret=" << Utils::hexToBase32(Secret) << "&digits=" << OtpOptions.GetDigits();

	return url.str();
}

UserInfo & UserInfo::SetPinNumber(const std::string & pin)
{
	PinNumber = pin;
	return *this;
}

UserInfo & UserInfo::SetMode(const std::string & mode)
{
	Mode = mode;
	return *this;
}

UserInfo & UserInfo::SetSecret(const std::string & secret)
{
	Secret = secret;
	return *this;
}

std::string UserInfo::GetPinNumber() const
{
	return PinNumber;
}

std::string UserInfo::GetMode() const
{
	return Mode;
}

std::string UserInfo::GetSecret() const
{
	return Secret;
}

std::string UserInfo::GetUserId() const
{
	return UserId;
}
