#include <iostream>
#include <string>
#include <vector>
#include "color_utils.h"
#include "hid_utils.h"

int main(int argc, char* argv[]) {
    if (argc < 4 || (argc - 1) % 3 != 0) {
        std::cerr << "Usage: ./program <vendor_id1> <product_id1> <hex_color1> [<vendor_id2> <product_id2> <hex_color2> ...]" << std::endl;
        return 1;
    }

    if (hid_init()) {
        std::cerr << "Failed to initialize HID API" << std::endl;
        return 1;
    }

    try {
        // Iterate through all provided VID/PID/color sets
        for (int i = 1; i < argc; i += 3) {
            unsigned short vendor_id = std::stoi(argv[i], nullptr, 16);
            unsigned short product_id = std::stoi(argv[i + 1], nullptr, 16);
            std::string hex_color = argv[i + 2];

            std::vector<unsigned char> rgb = hex_to_rgb(hex_color);
            std::vector<unsigned char> vibrant_rgb = make_color_vibrant(rgb, 2.0f);
            send_raw_report(vendor_id, product_id, vibrant_rgb);
        }
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        hid_exit();
        return 1;
    }

    hid_exit();
    return 0;
}
