#pragma once

#include <cstdint>
#include <span>
#include <vector>

#include "RenderUtils.hpp"

class Framebuffer {
   public:
    Framebuffer(int width, int height);

    int width() const { return m_width; }
    int height() const { return m_height; }

    void setPixel(int x, int y, const Color& color);
    Color getPixel(int x, int y);

    void setColumn(int x, int yStart, int yEnd, const Color& color);

    void clear(const Color& color = {16, 16, 16, 255});

    std::span<const Color> data() const { return m_pixels; }

   private:
    int m_width, m_height;
    std::vector<Color> m_pixels;

    size_t index(int x, int y) const { return static_cast<size_t>(y) * m_width + x; }
};