#pragma once

#include <array>
#include <cstdint>
#include <optional>
#include <span>
#include <string_view>
#include <vector>

class WadFile;

struct WadDirEntry {
    uint32_t filePos;
    uint32_t size;
    std::array<char, 8> name;
};

class WadDirectory {
   public:
    WadDirectory(const WadFile& file);

    const WadDirEntry* find(std::string_view name) const;
    std::optional<size_t> index(std::string_view name) const;

    std::span<const WadDirEntry> entries() const { return m_entries; }

   private:
    std::vector<WadDirEntry> m_entries;
};