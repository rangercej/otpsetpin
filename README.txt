Introduction
============
Userland tools to support pam_oath (http://www.nongnu.org/oath-toolkit/pam_oath.html )

Requires:
	pam_oath
	liboath
	libqrencode
	libgd
	g++
	gccmakedep

For building, then on Debian, apt-get install:
	liboath-dev     (Development header and OATH toolkit library)
	libqrencode-dev (QR generation library)
	libgd-dev       (Graphics library; used to create PNG from libqrencode)
	g++             (C++ compiler)
	xutils-dev      (For gccmakedep)

For using, then on Debian, apt-get install:
	libpam-oath   (PAM authentication module)


Caveat Emptor
=============

This is still a work in progress, with much to do. There will probably
be bugs. The stable branch is not guranteed to be bug free, but is a
stake in the ground where I consider the code to be probably okay 
for use (rather than default which is in constant flux and may not 
even build).


QuickStart/Overview
===================

Userland utils:
	otpsetpin - intended to be setgid, a utility to allow users
		to change their OTP pin

	otpgenurl - intended to be setgid, a utility to allow users
		to re-fetch their otpauth:// URL.

	otpgenqr - intended to be setgid, a utility to allow users
		to generate a QR code for themselves.

	otpadduser - intended to be ran by root, create an OTP entry for
		the user so they can log in using OTP.

	otpdeluser - intended to be ran by root, remove an OTP entry for
		the user, disabling OTP for them.

User configuration is in /etc/users.oath. This file should be root read-only
as it contains plaintext PIN and secret.

PAM configuration: I've added this line to the top of /etc/pam.d/sshd:

	auth required pam_oath.so usersfile=/etc/users.oath window=20 digits=6

I've also disabled password authentication (on Debian, comment out the line
that read "@include common-auth"; elsewhere, comment out the line that
reads something like "auth required pam_unix.so").

Client: I use FreeOTP for Android. Configuration - easiest way - generate a 
QR code from the otpauth:// URL otpadduser gives you and scan that into 
FreeOTP, or manually configure (tedious to type in the secret though).

