#include "color_utils.h"
#include <sstream>
#include <stdexcept>
#include <cmath>

std::vector<unsigned char> hex_to_rgb(const std::string& hex_color) {
    if (hex_color.length() != 6) {
        throw std::invalid_argument("Hex color must be 6 characters long.");
    }
    std::vector<unsigned char> rgb;
    for (int i = 0; i < 6; i += 2) {
        std::stringstream ss;
        ss << std::hex << hex_color.substr(i, 2);
        int value;
        ss >> value;
        rgb.push_back(static_cast<unsigned char>(value));
    }
    return rgb;
}

std::vector<unsigned char> make_color_vibrant(const std::vector<unsigned char>& rgb, float saturation_increase) {
    float r = rgb[0] / 255.0f;
    float g = rgb[1] / 255.0f;
    float b = rgb[2] / 255.0f;

    float max = std::fmax(r, std::fmax(g, b));
    float min = std::fmin(r, std::fmin(g, b));
    float l = (max + min) / 2.0f;

    float s;
    if (max == min) {
        s = 0.0f;
    } else {
        s = l > 0.5f ? (max - min) / (2.0f - max - min) : (max - min) / (max + min);
    }

    s = std::fmin(s * saturation_increase, 1.0f);

    std::vector<unsigned char> new_rgb = {
        static_cast<unsigned char>(r * 255),
        static_cast<unsigned char>(g * 255),
        static_cast<unsigned char>(b * 255)
    };

    return new_rgb;
}
