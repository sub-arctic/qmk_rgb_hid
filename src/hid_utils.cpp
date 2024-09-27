#include "hid_utils.h"
#include <iostream>
#include <memory>
#include <vector>

constexpr int report_length = 32;
constexpr unsigned short usage_page = 0xFF60;
constexpr unsigned short usage_id = 0x61;

// Get the Raw HID interface for the device with given VID and PID
hid_device* get_raw_hid_interface(unsigned short vendor_id, unsigned short product_id) {
    struct hid_device_info *devs, *cur_dev;
    
    devs = hid_enumerate(vendor_id, product_id);
    cur_dev = devs;

    hid_device* device = nullptr;

    while (cur_dev) {
        if (cur_dev->usage_page == usage_page && cur_dev->usage == usage_id) {
            device = hid_open_path(cur_dev->path);
            break;
        }
        cur_dev = cur_dev->next;
    }

    hid_free_enumeration(devs);

    return device;
}

// Send a raw HID report to the opened HID device
void send_raw_report(unsigned short vendor_id, unsigned short product_id, const std::vector<unsigned char>& rgb) {
    std::unique_ptr<hid_device, decltype(&hid_close)> device{
        get_raw_hid_interface(vendor_id, product_id), hid_close};

    if (!device) {
        std::cerr << "No device found" << std::endl;
        exit(1);
    }

    std::vector<unsigned char> report(report_length + 1, 0x00);
    report[1] = rgb[0];
    report[2] = rgb[1];
    report[3] = rgb[2];

    int result = hid_write(device.get(), report.data(), report_length + 1);
    if (result < 0) {
        std::cerr << "Error sending HID report: " << hid_error(device.get()) << std::endl;
    }
}
