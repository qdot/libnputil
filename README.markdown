# libnputil

by Kyle Machulis

[Nonpolynomial Labs](http://www.nonpolynomial.com)

## Description

There comes a time where you just have to admit to yourself that all
you're doing is adding like, one or two functions to a libusb
frontend, calling it a driver, and releasing it to the world. This
library is my admission of that.

I have at least 4 projects that simply add a single function to
libusb, or else use the exact same bastardization of the HID layer to
communicate. Instead of copying the code everywhere, I've created
libnputil. Now, libnputil isn't exactly a "library". It's really just
source files that I include into other source files and do some
preprocessor acrobatics with in order to create library specific
symbols. While one would normally just use a damn library for this,
99% of the users of my libraries don't really care to link yet another
library just to get the functionality of my drivers, and they very
rarely change versions or functionality. With that in mind, I bypass
the idea of library compilation and just move the symbols right on
into the library itself. It still allows for the libraries below
(libusb/windows ddk) to be switched out, but otherwise things look the
same because I very, very rarely change how I do device selection and
initialization at this level.

## Development Notes

I really wouldn't recommend using this if you aren't me. This is just
a utility library for me to keep my code sorted in a way that seems
slightly but not really sane to me.

## Library Requirements

* [CMake (Required on all platforms)](http://www.cmake.org)
* [WDK (Windows Only)](http://www.microsoft.com/whdc/devtools/WDK/default.mspx)
* [libusb-1.0 (All non-windows platforms)](http://www.libusb.org)
* [libusb-0.1 (Legacy, deprecated)](http://www.libusb.org)
