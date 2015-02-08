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
#ifndef __OTP_OTPERROR_H_
#define __OTP_OTPERROR_H_

class OtpError
{
	private:
		int ErrorType;
		int IntContext;
		std::string StringContext;

		bool HaveIntContext;
		bool HaveStringContext;

	public:
		struct ErrorCodes {
			enum Codes {
				NoError = 0,
				PinMismatch,
				AuthFileReadError,
				AuthFileWriteError,
				UserWriteError,
				IncorrectPin,
				UnknownUser,
				PermissionDenied,
				ConversionError,
				CannotDetermineUser,
				ConfBadOtpLength,
				ConfUnknownDirective
			};
		};

		OtpError (int errorType);
		OtpError (int errorType, int context);
		OtpError (int errorType, std::string context);

		std::string GetMessage() const;
		int GetErrorCode() const;;
};

#endif
