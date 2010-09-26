/***
 * @file nputil_libusb1.c
 * @brief LibUSB 1.0 (http://www.libusb.org/) utility functions
 * @author Kyle Machulis (kyle@nonpolynomial.com)
 * @copyright (c) 2009 Nonpolynomial Labs/Kyle Machulis
 * @license BSD License
 *
 */

#include "libusb-1.0/libusb.h"
#include <stdlib.h>

#define FNNAME(pre, post)  pre ## _ ## post
#define FNAME(pre, post) FNNAME(pre, post)
#define FUNCNAME(post) FNAME(NPUTIL_DEVICE_NAME, post)

NPUTIL_DEVICE_NAME* FUNCNAME(create)()
{
	NPUTIL_DEVICE_NAME* s = (NPUTIL_DEVICE_NAME*)malloc(sizeof(NPUTIL_DEVICE_NAME));
	s->_is_open = 0;
	s->_is_inited = 0;
	return s;
}

void FUNCNAME(delete)(NPUTIL_DEVICE_NAME* s)
{
	free(s);
}

int FUNCNAME(init)(NPUTIL_DEVICE_NAME* s)
{
	if(libusb_init(&s->_context) < 0)
	{
		return E_NPUTIL_DRIVER_ERROR;
	}
#if defined(LIBUSB_DEBUG)
	//Spam libusb messages
	//Between 0-3 for libusb 1.0
	libusb_set_debug(s->_context, 3);
#else
	libusb_set_debug(s->_context, 0);
#endif
	s->_is_inited = 1;
}

int FUNCNAME(get_count)(NPUTIL_DEVICE_NAME* s)
{
	struct libusb_device **devs;
	struct libusb_device *found = NULL;
	struct libusb_device *dev;
	size_t i = 0;
	int count = 0;

	if (!s->_is_inited)
	{
		return E_NPUTIL_NOT_INITED;
	}
	
	if (libusb_get_device_list(s->_context, &devs) < 0)
	{
		return E_NPUTIL_DRIVER_ERROR;
	}

	while ((dev = devs[i++]) != NULL)
	{
		struct libusb_device_descriptor desc;
		int dev_error_code;
		dev_error_code = libusb_get_device_descriptor(dev, &desc);
		if (dev_error_code < 0)
		{
			break;
		}
		if (desc.idVendor == NPUTIL_USB_VID && desc.idProduct == NPUTIL_USB_PID)
		{
			++count;
		}
	}

	libusb_free_device_list(devs, 1);
	return count;
}

int FUNCNAME(open)(NPUTIL_DEVICE_NAME* s, unsigned int index)
{
	struct libusb_device **devs;
	struct libusb_device *found = NULL;
	struct libusb_device *dev;
	size_t i = 0;
	int count = 0;
	int device_error_code = 0;

	if (!s->_is_inited)
	{
		return E_NPUTIL_NOT_INITED;
	}

	if ((device_error_code = libusb_get_device_list(s->_context, &devs)) < 0)
	{
		return E_NPUTIL_DRIVER_ERROR;
	}

	while ((dev = devs[i++]) != NULL)
	{
		struct libusb_device_descriptor desc;
		device_error_code = libusb_get_device_descriptor(dev, &desc);
		if (device_error_code < 0)
		{
			libusb_free_device_list(devs, 1);
			return E_NPUTIL_NOT_INITED;
		}
		if (desc.idVendor == NPUTIL_USB_VID && desc.idProduct == NPUTIL_USB_PID)
		{
			if(count == index)
			{
				found = dev;
				break;
			}
			++count;
		}
	}

	if (found)
	{
		device_error_code = libusb_open(found, &s->_device);
		if (device_error_code < 0)
		{
			libusb_free_device_list(devs, 1);
			return E_NPUTIL_NOT_INITED;
		}
	}
	else
	{
		return E_NPUTIL_NOT_INITED;		
	}
	s->_is_open = 1;
	return 0;
}

int FUNCNAME(close)(NPUTIL_DEVICE_NAME *s)
{
	if(!s->_is_open)
	{
		return E_NPUTIL_NOT_OPENED;
	}
	if (libusb_release_interface(s->_device, 0) < 0)
	{
		return E_NPUTIL_NOT_INITED;				
	}
	libusb_close(s->_device);
	s->_is_open = 0;
	return 0;
}
