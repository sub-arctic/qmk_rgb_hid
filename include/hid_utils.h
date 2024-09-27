#ifndef HID_UTILS_H
#define HID_UTILS_H

#include <vector>
#include <hidapi/hidapi.h>

// Get a Raw HID interface by vendor/product ID
hid_device* get_raw_hid_interface(unsigned short vendor_id, unsigned short product_id);

// Send raw HID report to the device
void send_raw_report(unsigned short vendor_id, unsigned short product_id, const std::vector<unsigned char>& rgb);

#endif
