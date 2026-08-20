#pragma once

#include <cstdint>
#include <limits>
#include <numbers>

using angle_t = uint32_t;

constexpr angle_t ANG1 = 0x0B60B60B;
constexpr angle_t ANG45 = 0x20000000;
constexpr angle_t ANG90 = 0x40000000;
constexpr angle_t ANG180 = 0x80000000;
constexpr angle_t ANG270 = 0xC0000000;

constexpr float angleToRad(angle_t a) {
    return (a / static_cast<float>(std::numeric_limits<uint32_t>::max()) * static_cast<float>(2.0 * std::numbers::pi));
}

constexpr angle_t degToAngle(int a) { return static_cast<angle_t>(a * 0x0B60B60BUL); }