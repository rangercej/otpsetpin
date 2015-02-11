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
#include <iostream>
#include <fstream>
#include <cstdlib>

extern "C" {
	#include "liboath/oath.h"
}

#include "secret.h"
#include "otperror.h"

//----------------------------------------------------------------------------
// Summary: Create a new secret
Secret::Secret()
{
	std::fstream randomStream("/dev/urandom");
	randomStream.read(SecretBytes, SecretLength);
}

//----------------------------------------------------------------------------
// Summary: Create a secret from an existing secret
// Params: Existing secret
Secret::Secret(std::string hexString)
{
	char bytes[128];
	size_t byteLen = sizeof(bytes);
	int ok = oath_hex2bin (hexString.c_str(), bytes, &byteLen);

	if (ok != OATH_OK) {
		throw OtpError(OtpError::ErrorCodes::ConversionError, ok);
	}

	if (byteLen != SecretLength) {
		throw OtpError(OtpError::ErrorCodes::BadSecret);
	}

	memcpy(SecretBytes, bytes, SecretLength);
}

//----------------------------------------------------------------------------
// Summary: Convert bytes to a hex string
// Params: None
// Returns: Hex version of the secret
std::string Secret::ToHexString()
{
	char hexBuffer[1024];
	oath_bin2hex(SecretBytes, SecretLength, hexBuffer);

	return std::string(hexBuffer);
}

//----------------------------------------------------------------------------
// Summary: Convert bytes to a base32 string
// Params: None
// Returns: Base32 version of the secret
std::string Secret::ToBase32String()
{
	char *b32Buffer;
	size_t b32Length;

	int ok = oath_base32_encode(SecretBytes, SecretLength, &b32Buffer, &b32Length);
	if (ok != OATH_OK) {
		throw OtpError(OtpError::ErrorCodes::ConversionError, ok);
	}

	std::string b32Secret(b32Buffer);
	::free(b32Buffer);

	return b32Secret;
}
