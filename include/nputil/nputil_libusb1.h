/***
 * @file nputil_libusb1.h
 * @brief LibUSB 1.0 (http://www.libusb.org/) utility functions
 * @author Kyle Machulis (kyle@nonpolynomial.com)
 * @copyright (c) 2009 Nonpolynomial Labs/Kyle Machulis
 * @license BSD License
 *
 */

// So you're probably all thinking, "Hey! This is a header
// file!". Well, it's not. It's a template. This is to be cut and
// pasted into another library and the names in it replaced. Why? Read
// the readme.

#ifndef NPUTIL_LIBUSB1_H
#define NPUTIL_LIBUSB1_H
#include "libusb-1.0/libusb.h"

#define E_NPUTIL_DRIVER_ERROR -1
#define E_NPUTIL_NOT_INITED -2
#define E_NPUTIL_NOT_OPENED -3

#ifndef NPUTIL_LIBUSB1_STRUCT
typedef struct {
	struct libusb_context* _context;
	struct libusb_device_handle* _device;
	struct libusb_transfer* _in_transfer;
	struct libusb_transfer* _out_transfer;
	int _is_open;
	int _is_inited;
} nputil_libusb1_struct;
#endif

#ifdef __cplusplus
extern "C" {
#endif
	nputil_libusb1_struct* nputil_libusb1_create_struct();
	void nputil_libusb1_delete_struct(nputil_libusb1_struct* s);
	int nputil_libusb1_init(nputil_libusb1_struct* s);
	int nputil_libusb1_count(nputil_libusb1_struct* s, int vendor_id, int product_id);
	int nputil_libusb1_open(nputil_libusb1_struct* s, int vendor_id, int product_id, int index);
	int nputil_libusb1_close(nputil_libusb1_struct* s);
#ifdef __cplusplus
}
#endif

#endif //NPUTIL_LIBUSB1_H
