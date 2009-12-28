/***
 * @file nputil_libusb-1.0.h
 * @brief LibUSB 1.0 (http://www.libusb.org/) utility functions
 * @author Kyle Machulis (kyle@nonpolynomial.com)
 * @copyright (c) 2009 Nonpolynomial Labs/Kyle Machulis
 * @license BSD License
 *
 */

#include "libusb.h"

typedef struct {
	struct libusb_context* _context;
	struct libusb_device_handle* _device;
	struct libusb_transfer* _in_transfer;
	struct libusb_transfer* _out_transfer;
	int _is_open;
	int _is_inited;
} nputil_libusb1_struct;

nputil_libusb1_struct* nputil_libusb1_create_struct();
void nputil_libusb1_delete_struct();
int nputil_libusb1_init(nputil_libusb1_struct* s);
int nputil_libusb1_count(nputil_libusb1_struct* s, int vendor_id, int product_id);
int nputil_libusb1_open(nputil_libusb1_struct* s, int vendor_id, int product_id, int index);
int nputil_libusb1_close(nputil_libusb1_struct* s);
