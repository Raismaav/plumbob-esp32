#ifndef COLOR_UTILS_H
#define COLOR_UTILS_H

#include <Arduino.h>

// ====== RGB COLOR STRUCTURE ======
struct RGB { 
    uint8_t r, g, b; 
};

// ====== COLOR CONVERSION FUNCTIONS ======

/**
 * Convert hex string to RGB color
 * @param hex String with 6 hexadecimal characters (e.g., "34C759")
 * @return RGB structure with color values
 */
RGB hexToRGB(const String& hex) {
    RGB o{0, 0, 0};
    if (hex.length() != 6) return o;
    
    auto hx = [](char c) -> uint8_t {
        if (c >= '0' && c <= '9') return c - '0';
        if (c >= 'a' && c <= 'f') return 10 + (c - 'a');
        if (c >= 'A' && c <= 'F') return 10 + (c - 'A');
        return 0;
    };
    
    o.r = (hx(hex[0]) << 4) | hx(hex[1]);
    o.g = (hx(hex[2]) << 4) | hx(hex[3]);
    o.b = (hx(hex[4]) << 4) | hx(hex[5]);
    return o;
}

/**
 * Convert mood name to RGB color (Sims Plumbob moods)
 * @param mood Mood name string
 * @param c RGB structure to store the result
 */
void moodToRGB(const String& mood, RGB& c) {
    if (mood == "happy")              c = {0x34, 0xC7, 0x59};
    else if (mood == "inspired")      c = {0x2D, 0xD6, 0xC1};
    else if (mood == "focused")       c = {0x0A, 0x84, 0xFF};
    else if (mood == "confident")     c = {0xFF, 0x95, 0x00};
    else if (mood == "playful")       c = {0xAF, 0x52, 0xDE};
    else if (mood == "flirty")        c = {0xFF, 0x2D, 0x55};
    else if (mood == "sad")           c = {0x0B, 0x3D, 0x91};
    else if (mood == "angry")         c = {0xFF, 0x3B, 0x30};
    else if (mood == "uncomfortable") c = {0xFF, 0xD6, 0x0A};
    else if (mood == "tense")         c = {0xFF, 0xB3, 0x00};
    else if (mood == "fine")          c = {0xFF, 0xFF, 0xFF};
}

#endif // COLOR_UTILS_H

