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
#include <cerrno>

extern "C" {
#include <sys/stat.h>
}

#include <qrencode.h>
#include <gd.h>

#include "userinfo.h"
#include "utils.h"
#include "options.h"
#include "secret.h"
#include "otperror.h"

UserInfo::UserInfo(const std::string & userId, const Options & options)
{
	OtpOptions = options;
	AuthFileName = options.GetAuthFile();
	UserId = userId;
	Mode = "";
	PinNumber = "";
	SharedSecret = "";
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
			SharedSecret = secret;
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
		int status = chmod (tempFile.c_str(), S_IRUSR | S_IWUSR);
		if (status != 0) {
			throw OtpError(OtpError::ErrorCodes::AuthFilePermsError, status);
		}
		if (newAuthFile.fail()) {
			throw OtpError(OtpError::ErrorCodes::AuthFileWriteError);
		}

		while (authFile >> type >> userin >> pin >> secret && std::getline(authFile, temp)) {
			if (userin != UserId) {
				newAuthFile << type << " " << userin << " " << pin << " " << secret << " " << temp << std::endl;
			} else {
				userwrote = true;
				if (userAction != UserAction::Delete) {
					newAuthFile << Mode << " " << UserId << " " << PinNumber << " " << SharedSecret << " " << temp << std::endl;
				}
			}
		}

		if (!userwrote && userAction == UserAction::Create) {
			newAuthFile << Mode << " " << UserId << " " << PinNumber << " " << SharedSecret << " " << std::endl;
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

	Secret secret(SharedSecret);

	url << "otpauth://totp/" << OtpOptions.GetIssuer() << ":" << UserId << "@" << Utils::getHostName() << "?secret=" << secret.ToBase32String() << "&digits=" << OtpOptions.GetDigits();

	return url.str();
}

//----------------------------------------------------------------------------
// Summary: Set the user's PIN
// Params: User's PIN
// Returns: this object for method chaining
UserInfo & UserInfo::SetPinNumber(const std::string & pin)
{
	PinNumber = pin;
	return *this;
}

//----------------------------------------------------------------------------
// Summary: Set the user's OTP mode
// Params: OTP mode string
// Returns: this object for method chaining
UserInfo & UserInfo::SetMode(const std::string & mode)
{
	Mode = mode;
	return *this;
}

//----------------------------------------------------------------------------
// Summary: Set the user's secret
// Params: Secret value
// Returns: this object for method chaining
UserInfo & UserInfo::SetSecret(const std::string & secret)
{
	SharedSecret = secret;
	return *this;
}

//----------------------------------------------------------------------------
// Summary: Get the PIN for the current user
// Params: none
// Returns: PIN for the current user
std::string UserInfo::GetPinNumber() const
{
	return PinNumber;
}

//----------------------------------------------------------------------------
// Summary: Get the OTP mode string for the current user
// Params: none
// Returns: OTP mode for the current user
std::string UserInfo::GetMode() const
{
	return Mode;
}

//----------------------------------------------------------------------------
// Summary: Get the secret for the current user
// Params: none
// Returns: Secret for the current user
std::string UserInfo::GetSecret() const
{
	return SharedSecret;
}

//----------------------------------------------------------------------------
// Summary: Get the user ID for this instance
// Params: none
// Returns: The current user ID
std::string UserInfo::GetUserId() const
{
	return UserId;
}

//----------------------------------------------------------------------------
// Summary: Generate QR code for user
// Params:
//	outputFileName - name of the file to write the QR code to.
// Returns: none
void UserInfo::GetQrCode(std::string outputFileName) const
{
	std::string url = GetUrl();

	QRcode *qrCode = QRcode_encodeString(url.c_str(), 0, QR_ECLEVEL_Q, QR_MODE_8, 1);
	if (qrCode == NULL) {
		throw OtpError(OtpError::ErrorCodes::QrEncodeStringFail, errno);
	}

	FILE *outfile;
	gdImagePtr image;
	int white, black;
	
	image = gdImageCreate((2 + qrCode->width) * QrPixelSize, (2 + qrCode->width) * QrPixelSize);
	white = gdImageColorAllocate(image, 255, 255, 255);	
	black = gdImageColorAllocate(image, 0, 0, 0);

	for (int i = 0; i < qrCode->width + 2; i++) {
		SetPixel(image, 0, i, white);
	}
	for (int i = 0; i < qrCode->width * qrCode->width; i++) {
		int row = 1 + (i / qrCode->width);
		int col = 1 + (i % qrCode->width);
		int color = (qrCode->data[i] & 1) == 1 ? black : white;

		if (col == 1) {
			SetPixel(image, row, 0, white);
		}
		SetPixel(image, row, col, color);
		if (col == qrCode->width) {
			SetPixel(image, row, 1 + col, white);
		}
	}
	for (int i = 0; i < qrCode->width + 2; i++) {
		SetPixel(image, 2 + qrCode->width, i, white);
	}

	outfile = fopen(outputFileName.c_str(), "wb");
	gdImagePng(image, outfile);
	fclose(outfile);
	gdImageDestroy(image);
}

//----------------------------------------------------------------------------
// Summary: Set a colour block in the output image
// Params:
//	image - GD image object
//	row - which row to set the block
//	col - which col to set the block
//	colour - colour to set the block to
// Returns: none
void UserInfo::SetPixel(gdImagePtr image, int row, int col, int colour) const
{
	int colStart = col * QrPixelSize;
	int rowStart = row * QrPixelSize;

	for (int x = 0; x < QrPixelSize; x++) {
		for (int y = 0; y < QrPixelSize; y++) {
			gdImageSetPixel(image, colStart + x, rowStart + y, colour);
		}
	}
}
