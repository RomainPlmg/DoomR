#pragma once

#include <cstdint>

using fixed_t = int32_t;

constexpr int FRACBITS = 16;
constexpr fixed_t FRACUNIT = 1 << FRACBITS;  // 65536 = "1.0", 16.16 format

constexpr fixed_t FixedMul(fixed_t a, fixed_t b) {
    return static_cast<fixed_t>((static_cast<int64_t>(a) * b) >> FRACBITS);
}

constexpr fixed_t FixedDiv(fixed_t a, fixed_t b) {
    return static_cast<fixed_t>((static_cast<int64_t>(a) << FRACBITS) / b);
}

constexpr fixed_t IntToFixed(int i) { return i * FRACUNIT; }
constexpr int FixedToInt(fixed_t f) { return f >> FRACBITS; }
constexpr float FixedToFloat(fixed_t f) { return f / static_cast<float>(FRACUNIT); }