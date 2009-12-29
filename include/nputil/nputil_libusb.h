/***
 * @file nputil_libusb.h
 * @brief LibUSB 0.1 (http://www.libusb.org/) utility functions
 * @author Kyle Machulis (kyle@nonpolynomial.com)
 * @copyright (c) 2009 Nonpolynomial Labs/Kyle Machulis
 * @license BSD License
 *
 */

#ifndef NPUTIL_LIBUSB_H
#define NPUTIL_LIBUSB_H

#include "usb.h"

typedef struct {
	struct usb_dev_handle* _device;
	int _is_open;
	int _is_inited;
} nputil_libusb_struct;

#ifdef __cplusplus
extern "C" {
#endif

nputil_libusb_struct* nputil_libusb_create_struct();
void nputil_libusb_delete_struct();
int nputil_libusb_init(nputil_libusb_struct* s);
int nputil_libusb_count(nputil_libusb_struct* s, int vendor_id, int product_id);
int nputil_libusb_open(nputil_libusb_struct* s, int vendor_id, int product_id, int index);
void nputil_libusb_close(nputil_libusb_struct* s);
#ifdef __cplusplus
}
#endif

#endif //NPUTIL_LIBUSB_H
