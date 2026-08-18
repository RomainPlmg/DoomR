#pragma once

#include <string_view>

enum class WadError {
    FileNotFound,
    IoError,
    TooSmall,
    BadMagic,
    CorruptDirectory,
};

constexpr std::string_view toString(WadError e) noexcept {
    switch (e) {
        case WadError::FileNotFound:
            return "File not found";
        case WadError::IoError:
            return "I/O error";
        case WadError::TooSmall:
            return "File too small";
        case WadError::BadMagic:
            return "Bad magic number (not an IWAD/PWAD)";
        case WadError::CorruptDirectory:
            return "Corrupt directory table";
    }
    return "Unknown WadError";
}