#include "Map.hpp"

#include <algorithm>

std::unique_ptr<Map> Map::load(const WadFile& file, const WadDirectory& dir, std::string_view mapName) {
    auto mapIndexOpt = dir.index(mapName);
    if (!mapIndexOpt.has_value()) {
        LOG_ERROR("Map '{}' not found in WAD.", mapName);
        return nullptr;
    }

    LOG_INFO("Loading map '{}'...", mapName);

    std::unique_ptr<Map> map(new Map());

    size_t mapIndex = mapIndexOpt.value();

    // Read all lumps of the map
    WadDirEntry entry{};
    // THINGS
    if (!loadLump(file, dir, mapIndex + 1, map->m_things)) return nullptr;
    // LINEDEFS
    if (!loadLump(file, dir, mapIndex + 2, map->m_linedefs)) return nullptr;
    // SIDEDEFS
    if (!loadLump(file, dir, mapIndex + 3, map->m_sidedefs)) return nullptr;
    // VERTEXES
    if (!loadLump(file, dir, mapIndex + 4, map->m_vertexes)) return nullptr;

    return map;
}

BBox Map::computeBoundingBox() const {
    const auto [minXIt, maxXIt] = std::ranges::minmax_element(m_vertexes, {}, &Vertex::x);
    const auto [minYIt, maxYIt] = std::ranges::minmax_element(m_vertexes, {}, &Vertex::y);

    return {
        maxYIt->y,
        minYIt->y,
        minXIt->x,
        maxXIt->x,
    };
}