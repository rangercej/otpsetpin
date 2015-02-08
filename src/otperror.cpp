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

#include "otperror.h"

OtpError::OtpError(int errorCode)
{
	ErrorType = errorCode;
	HaveIntContext = false;
	HaveStringContext = false;
}

OtpError::OtpError(int errorCode, int context)
{
	ErrorType = errorCode;
	IntContext = context;
	HaveIntContext = true;
	HaveStringContext = false;
}

OtpError::OtpError(int errorCode, std::string context)
{
	ErrorType = errorCode;
	StringContext = context;
	HaveIntContext = false;
	HaveStringContext = true;
}

std::string OtpError::GetMessage() const
{
	std::ostringstream errorText;

	switch (ErrorType) {
		case ErrorCodes::NoError:
			errorText << "No error";
			break;
		case ErrorCodes::PinMismatch:
			errorText << "PINs do not match";
			break;
		case ErrorCodes::AuthFileReadError:
			errorText <<  "Could not open auth file for reading";
			break;
		case ErrorCodes::AuthFileWriteError:
			errorText <<  "Could not open auth file for writing";
			break;
		case ErrorCodes::UserWriteError:
			errorText <<  "Unexpected failure to update auth file for user";
			break;
		case ErrorCodes::IncorrectPin:
			errorText <<  "Incorrect PIN";
			break;
		case ErrorCodes::UnknownUser:
			errorText <<  "Unknown user provided";
			break;
		case ErrorCodes::PermissionDenied:
			errorText <<  "Permission denied";
			break;
		case ErrorCodes::ConversionError:
			errorText <<  "Error converting hex string";
			break;
		case ErrorCodes::CannotDetermineUser:
			errorText <<  "Unable to determine current user";
			break;
		case ErrorCodes::ConfBadOtpLength:
			errorText <<  "'otplength' must either be '6' or '8'";
			break;
		case ErrorCodes::ConfUnknownDirective:
			errorText <<  "Unknown configuration directive";
			break;
		default:
			errorText <<  "Unknown error:" << ErrorType;
	}

	if (HaveStringContext) {
		errorText << ": " << StringContext;
	}

	if (HaveIntContext) {
		errorText << ": " << IntContext;
	}

	errorText << ".";

	return errorText.str();
}

int OtpError::GetErrorCode() const
{
	return ErrorType;
}
