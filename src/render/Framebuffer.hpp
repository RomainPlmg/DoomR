#pragma once

#include <cstdint>
#include <span>
#include <vector>

class Framebuffer {
   public:
    Framebuffer(int width, int height);

    int width() const { return m_width; }
    int height() const { return m_height; }

    void setPixel(int x, int y, uint8_t colorIdx);
    uint8_t getPixel(int x, int y);

    void setColumn(int x, int yStart, int yEnd, uint8_t colorIdx);

    void clear(uint8_t colorIdx = 0);

    std::span<const uint8_t> data() const { return m_pixels; }

   private:
    int m_width, m_height;
    std::vector<uint8_t> m_pixels;

    size_t index(int x, int y) const { return static_cast<size_t>(y) * m_width + x; }
};