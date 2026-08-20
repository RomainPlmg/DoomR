#pragma once

#include <cstdint>

struct Color {
    uint8_t r{0};
    uint8_t g{0};
    uint8_t b{0};
    uint8_t a{255};
};

struct Point {
    int x;
    int y;
};

struct ScreenRect {
    uint32_t top, bottom, left, right;
};