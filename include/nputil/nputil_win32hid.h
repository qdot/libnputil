/***
 * @file nputil_win32hid.h
 * @brief Utilities for communications via raw HID device reports through win32 calls
 * @author Kyle Machulis (kyle@nonpolynomial.com)
 * @copyright (c) 2009 Nonpolynomial Labs/Kyle Machulis
 * @license BSD License
 *
 */

#ifndef NPUTIL_WIN32HID_H
#define NPUTIL_WIN32HID_H
#include <windows.h>

typedef struct {
	HANDLE* _device;
	int _is_open;
	int _is_inited;
} nputil_win32hid_struct;

#ifdef __cplusplus
extern "C" {
#endif

nputil_win32hid_struct* nputil_win32hid_create_struct();
void nputil_win32hid_delete_struct(nputil_win32hid_struct* d);
int nputil_win32hid_init(nputil_win32hid_struct* s);
int nputil_win32hid_count(nputil_win32hid_struct* s, int vendor_id, int product_id);
int nputil_win32hid_open(nputil_win32hid_struct* s, int vendor_id, int product_id, int index);
int nputil_win32hid_close(nputil_win32hid_struct* s);

#ifdef __cplusplus
}
#endif
#endif //NPUTIL_WIN32HID_H
