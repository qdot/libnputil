/***
 * @file nputil_libusb-1.c
 * @brief LibUSB 1.0 (http://www.libusb.org/) utility functions
 * @author Kyle Machulis (kyle@nonpolynomial.com)
 * @copyright (c) 2009 Nonpolynomial Labs/Kyle Machulis
 * @license BSD License
 *
 */

#include "nputil_libusb1.h"
#include <stdlib.h>

nputil_libusb1_struct* nputil_libusb1_create_struct()
{
	nputil_libusb1_struct* s = (nputil_libusb1_struct*)malloc(sizeof(nputil_libusb1_struct));
	s->_is_open = 0;
	s->_is_inited = 0;
	return s;
}

void nputil_libusb1_delete_struct(nputil_libusb1_struct* s)
{
	free(s);
}

int nputil_libusb1_init(nputil_libusb1_struct* s)
{
	if(libusb_init(&s->_context) < 0)
	{
		return -1;
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

int nputil_libusb1_count(nputil_libusb1_struct* s, int vendor_id, int product_id)
{
	struct libusb_device **devs;
	struct libusb_device *found = NULL;
	struct libusb_device *dev;
	size_t i = 0;
	int count = 0;

	if (libusb_get_device_list(s->_context, &devs) < 0)
	{
		return -1;
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
		if (desc.idVendor == vendor_id && desc.idProduct == product_id)
		{
			++count;
		}
	}

	libusb_free_device_list(devs, 1);
	return count;
}

int nputil_libusb1_open(nputil_libusb1_struct* s, int vendor_id, int product_id, int index)
{
	struct libusb_device **devs;
	struct libusb_device *found = NULL;
	struct libusb_device *dev;
	size_t i = 0;
	int count = 0;
	int device_error_code = 0;

	if ((device_error_code = libusb_get_device_list(s->_context, &devs)) < 0)
	{
		return -1;
	}

	while ((dev = devs[i++]) != NULL)
	{
		struct libusb_device_descriptor desc;
		device_error_code = libusb_get_device_descriptor(dev, &desc);
		if (device_error_code < 0)
		{
			libusb_free_device_list(devs, 1);
			return -1;
		}
		if (desc.idVendor == vendor_id && desc.idProduct == product_id)
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
			return -1;
		}
	}
	else
	{
		return -1;
	}
	s->_is_open = 1;
	return 0;
}

int nputil_libusb1_close(nputil_libusb1_struct *s)
{
	
	if (libusb_release_interface(s->_device, 0) < 0)
	{
		return -1;
	}
	libusb_close(s->_device);
	s->_is_open = 0;
	return 0;
}
