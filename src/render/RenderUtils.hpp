#pragma once

#include <cstdint>

struct Color {
    uint8_t r;
    uint8_t g;
    uint8_t b;
    uint8_t a;
};

struct Point {
    int x;
    int y;
};

struct ScreenRect {
    uint32_t top, bottom, left, right;
};