#include "MapViewport.hpp"

MapViewport::MapViewport(uint32_t screenWidth, uint32_t screenHeight, const BBox& mapBounds)
    : m_screenWidth(screenWidth), m_screenHeight(screenHeight), m_worldOrigin({mapBounds.left, mapBounds.bottom}) {
    uint32_t mapWidth = mapBounds.right - mapBounds.left;
    uint32_t mapHeight = mapBounds.top - mapBounds.bottom;

    float scaleX = static_cast<float>(m_screenWidth - 1) / mapWidth;
    float scaleY = static_cast<float>(m_screenHeight - 1) / mapHeight;

    m_scale = std::min(scaleX, scaleY);

    float usedWidth = mapWidth * m_scale;
    float usedHeight = mapHeight * m_scale;
    m_offsetX = (m_screenWidth - usedWidth) * 0.5f;
    m_offsetY = (m_screenHeight - usedHeight) * 0.5f;
}

Point MapViewport::worldToScreen(const Vec2& point) const {
    float px = (point.x - m_worldOrigin.x) * m_scale + m_offsetX;
    float py = (point.y - m_worldOrigin.y) * m_scale + m_offsetY;

    return {static_cast<int>(px), static_cast<int>(m_screenHeight - 1 - py)};
}