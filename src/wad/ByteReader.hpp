#pragma once

#include <array>
#include <cstddef>
#include <cstdint>
#include <span>
#include <stdexcept>

inline uint32_t readU32(std::span<const std::byte> data, size_t offset) {
    if (static_cast<uint64_t>(offset) + sizeof(uint32_t) > data.size()) {
        throw std::out_of_range("readU32: offset out of bounds");
    }

    return static_cast<std::uint32_t>(data[offset])               // Byte 1
           | static_cast<std::uint32_t>(data[offset + 1]) << 8    // Byte 2
           | static_cast<std::uint32_t>(data[offset + 2]) << 16   // Byte 3
           | static_cast<std::uint32_t>(data[offset + 3]) << 24;  // Byte 4
}

inline int32_t readI32(std::span<const std::byte> data, std::size_t offset) {
    return static_cast<std::int32_t>(readU32(data, offset));
}

inline uint16_t readU16(std::span<const std::byte> data, std::size_t offset) {
    if (offset + sizeof(uint16_t) > data.size()) {
        throw std::out_of_range("readU16: offset out of bounds");
    }

    return static_cast<std::uint16_t>(static_cast<std::uint32_t>(data[offset])               // Byte 1
                                      | static_cast<std::uint32_t>(data[offset + 1]) << 8);  // Byte 2
}

inline int16_t readI16(std::span<const std::byte> data, std::size_t offset) {
    return static_cast<std::int16_t>(readU16(data, offset));
}

inline std::array<char, 8> readArray8(std::span<const std::byte> data, std::size_t offset) {
    if (offset + 8 > data.size()) {
        throw std::out_of_range("readArray8: offset out of bounds");
    }

    std::array<char, 8> name{};
    for (size_t i = 0; i < 8; ++i) {
        name[i] = static_cast<char>(data[offset + i]);
    }

    return name;
}