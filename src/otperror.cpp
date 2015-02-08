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
#include "otperror.h"

OtpError::OtpError(int errorCode)
{
	ErrorType = errorCode;
}

OtpError::OtpError(int errorCode, int context)
{
	ErrorType = errorCode;
	IntContext = context;
}

OtpError::OtpError(int errorCode, std::string context)
{
	ErrorType = errorCode;
	StringContext = context;
}

std::string OtpError::GetMessage() const
{
	switch (ErrorType) {
		case ErrorCodes::NoError:
			return "No error.";
		case ErrorCodes::PinMismatch:
			return "PINs do not match.";
		case ErrorCodes::AuthFileReadError:
			return "Could not open auth file for reading.";
		case ErrorCodes::AuthFileWriteError:
			return "Could not open auth file for writing.";
		case ErrorCodes::UserWriteError:
			return "Unexpected failure to update auth file for user.";
		case ErrorCodes::IncorrectPin:
			return "Incorrect PIN.";
		case ErrorCodes::UnknownUser:
			return "Unknown user provided.";
		case ErrorCodes::PermissionDenied:
			return "Permission denied";
		case ErrorCodes::ConversionError:
			return "Error converting hex string";
		case ErrorCodes::CannotDetermineUser:
			return "Unable to determine current user.";
		case ErrorCodes::ConfBadOtpLength:
			return "'otplength' must either be '6' or '8'.";
		case ErrorCodes::ConfUnknownDirective:
			return "Unknown configuration directive.";
		default:
			return "Unknown error";
	}
}

int OtpError::GetErrorCode() const
{
	return ErrorType;
}
