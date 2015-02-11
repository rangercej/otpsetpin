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
#ifndef __OTP_USERINFO_H_
#define __OTP_USERINFO_H_

#include "options.h"

class UserInfo {

	private:
		struct UserAction {
			enum Actions { Create, Update, Delete };
		};

		std::string AuthFileName;
		Options OtpOptions;

		std::string UserId;
		std::string PinNumber;
		std::string Mode;
		std::string SharedSecret;

		void UpdateUserFile(int userAction);

		void Get();

	public:
		UserInfo(const std::string & userId, const Options & options);
		void Update();
		void Create();
		void Delete();

		UserInfo & SetPinNumber(const std::string &);
		UserInfo & SetMode(const std::string &);
		UserInfo & SetSecret(const std::string &);

		std::string GetPinNumber() const;
		std::string GetMode() const;
		std::string GetSecret() const;
		std::string GetUserId() const;
		std::string GetUrl() const;
};

#endif
