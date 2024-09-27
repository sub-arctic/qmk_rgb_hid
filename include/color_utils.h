#ifndef COLOR_UTILS_H
#define COLOR_UTILS_H

#include <string>
#include <vector>

// Convert a hex color string to RGB components
std::vector<unsigned char> hex_to_rgb(const std::string& hex_color);

// Make a color more vibrant by adjusting saturation levels
std::vector<unsigned char> make_color_vibrant(const std::vector<unsigned char>& rgb, float saturation_increase = 1.5f);

#endif
