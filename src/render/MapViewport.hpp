#pragma once

#include "RenderUtils.hpp"
#include "core/Math.hpp"

class MapViewport {
   public:
    MapViewport(uint32_t screenWidth, uint32_t screenHeight, const BBox& mapBounds);

    Point worldToScreen(const Vec2& point) const;

   private:
    float m_scale;
    Vec2 m_worldOrigin;
    uint32_t m_screenWidth, m_screenHeight;
    int m_offsetX, m_offsetY;
};