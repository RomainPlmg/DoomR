#pragma once

#include <cstdint>
#include <expected>
#include <filesystem>
#include <memory>
#include <vector>

#include "WadError.hpp"

class WadFile {
   public:
    static std::expected<std::unique_ptr<WadFile>, WadError> open(const std::filesystem::path& path);

   private:
    WadFile() = default;
    std::vector<std::byte> m_data{};
    uint32_t m_nbLumps = 0;
    uint32_t m_infoTableOfs = 0;
};