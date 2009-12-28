/***
 * @file nputil_libusb1.c
 * @brief LibUSB 1.0 (http://www.libusb.org/) utility functions
 * @author Kyle Machulis (kyle@nonpolynomial.com)
 * @copyright (c) 2009 Nonpolynomial Labs/Kyle Machulis
 * @license BSD License
 *
 */

#include "nputil_libusb1.h"
#include <stdlib.h>

nputil_libusb_struct* nputil_libusb_create_struct()
{
	nputil_libusb_struct* s = (nputil_libusb_struct*)malloc(sizeof(nputil_libusb_struct));
	s->_is_open = 0;
	s->_is_inited = 0;
	return s;
}

void nputil_libusb_delete_struct(nputil_libusb_struct* s)
{
	free(s);
}

int nputil_libusb_init(nputil_libusb_struct* s)
{
	usb_init();
	s->_is_inited = 1;
}

int nputil_libusb_count(nputil_libusb_struct* s, int vendor_id, int product_id)
{
	int device_count = 0;	
	struct usb_bus* bus;
	struct usb_device* dev;

	//We re-run init on every get count, just in case new hubs/devices have been added
    usb_find_busses();
    usb_find_devices();
	for (bus = usb_get_busses(); bus != 0; bus = bus->next) 
	{			
		for (dev = bus->devices; dev != 0; dev = dev->next) 
		{
			if (dev->descriptor.idVendor == vendor_id && dev->descriptor.idProduct == product_id)
			{
				++device_count;
			}
		}
	}
	return device_count;
}

int nputil_libusb_open(nputil_libusb_struct* s, int vendor_id, int product_id, int index)
{
	int device_count = 0;
	struct usb_bus* bus;
	struct usb_device* dev;
	
	for (bus = usb_get_busses(); bus != 0; bus = bus->next) 
	{			
		for (dev = bus->devices; dev != 0; dev = dev->next) 
		{	
			if (dev->descriptor.idVendor == vendor_id && 
				dev->descriptor.idProduct == product_id)
			{
				if(device_count == device_index)
				{
					s->_device = usb_open(dev);
					if (s->_device) 
					{
						return device_count;
					}
				}
				++device_count;
			}
		}
	}	
	return -1;
}

void nputil_libusb_close(nputil_libusb_struct *s)
{
	if(!s->_device) return;
	usb_close(s->_device);	
}
