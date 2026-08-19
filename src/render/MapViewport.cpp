#include "MapViewport.hpp"

constexpr int PADDING = 20;  // 20px padding

MapViewport::MapViewport(uint32_t screenWidth, uint32_t screenHeight, const BBox& mapBounds)
    : m_screenWidth(screenWidth), m_screenHeight(screenHeight), m_worldOrigin({mapBounds.left, mapBounds.bottom}) {
    uint32_t mapWidth = mapBounds.right - mapBounds.left;
    uint32_t mapHeight = mapBounds.right - mapBounds.left;

    m_scaleX = (m_screenWidth - 1 - PADDING * 2) / static_cast<float>(mapWidth);
    m_scaleY = (m_screenHeight - 1 - PADDING * 2) / static_cast<float>(mapHeight);
}

Point MapViewport::worldToScreen(const Vec2& point) const {
    float px = (point.x - m_worldOrigin.x) * m_scaleX + PADDING;
    float py = (point.y - m_worldOrigin.y) * m_scaleY + PADDING;

    return {static_cast<int>(px), static_cast<int>(m_screenHeight - 1 - PADDING * 2 - py)};
}