#pragma once

#include <algorithm>
#include <cmath>

#include "Angle.hpp"
#include "Fixed.hpp"

struct Vec2 {
    int16_t x, y;
};

struct FVec2 {
    fixed_t x, y;
};

struct BBox {
    int16_t top, bottom, left, right;
    bool intersects(const BBox& other) const {
        return !(left > other.right) || (right < other.left || top < other.bottom || bottom > other.top);
    }
};

struct FBBox {
    fixed_t top, bottom, left, right;
    bool intersects(const BBox& other) const {
        return !(left > other.right) || (right < other.left || top < other.bottom || bottom > other.top);
    }
};

inline fixed_t angleCos(angle_t a) {
    float rad = angleToRad(a);
    return static_cast<fixed_t>(std::cos(rad) * FRACUNIT);
}

inline fixed_t angleSin(angle_t a) {
    float rad = angleToRad(a);
    return static_cast<fixed_t>(std::sin(rad) * FRACUNIT);
}

inline fixed_t angleTan(angle_t a) {
    float rad = angleToRad(a);
    float t = std::tan(rad);
    t = std::clamp(t, -128.f, 128.f);
    return static_cast<fixed_t>(t * FRACUNIT);
}