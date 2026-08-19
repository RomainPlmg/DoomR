#pragma once

#include <memory>
#include <span>
#include <string_view>
#include <vector>

#include "MapTypes.hpp"
#include "core/Log.hpp"
#include "core/Math.hpp"
#include "wad/WadDirectory.hpp"
#include "wad/WadFile.hpp"

class Map {
   public:
    static std::unique_ptr<Map> load(const WadFile& file, const WadDirectory& dir, std::string_view mapName);

    BBox computeBoundingBox() const;

    [[nodiscard]] const std::vector<Thing>& things() const { return m_things; }
    [[nodiscard]] const std::vector<Linedef>& linedefs() const { return m_linedefs; }
    [[nodiscard]] const std::vector<Sidedef>& sidedefs() const { return m_sidedefs; }
    [[nodiscard]] const std::vector<Vertex>& vertexes() const { return m_vertexes; }

   private:
    Map() = default;

    template <typename T>
    static bool loadLump(const WadFile& file, const WadDirectory& dir, size_t lumpIdx, std::vector<T>& out) {
        const WadDirEntry& entry = dir.entries()[lumpIdx];

        if (entry.size % sizeof(T) != 0) {
            LOG_ERROR("Lump '{}' size ({}) is not a multiple of struct size ({}).", entry.name, entry.size, sizeof(T));
            return false;
        }

        std::span<const std::byte> bytes = file.readLump(entry);

        size_t count = bytes.size() / sizeof(T);
        out.resize(count);
        memcpy(out.data(), bytes.data(), bytes.size());

        return true;
    }

    std::vector<Thing> m_things;
    std::vector<Linedef> m_linedefs;
    std::vector<Sidedef> m_sidedefs;
    std::vector<Vertex> m_vertexes;
};