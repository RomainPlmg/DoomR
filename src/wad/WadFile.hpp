#pragma once

#include <cstdint>
#include <expected>
#include <filesystem>
#include <memory>
#include <span>
#include <vector>

#include "WadError.hpp"

struct WadDirEntry;

class WadFile {
   public:
    static std::expected<std::unique_ptr<WadFile>, WadError> open(const std::filesystem::path& path);

    std::span<const std::byte> readLump(const WadDirEntry& entry) const;

    [[nodiscard]] std::span<const std::byte> data() const noexcept { return m_data; }
    [[nodiscard]] uint32_t nbLumps() const noexcept { return m_nbLumps; }
    [[nodiscard]] uint32_t infoTableOfs() const noexcept { return m_infoTableOfs; }

   private:
    WadFile() = default;
    std::vector<std::byte> m_data{};
    uint32_t m_nbLumps = 0;
    uint32_t m_infoTableOfs = 0;
};