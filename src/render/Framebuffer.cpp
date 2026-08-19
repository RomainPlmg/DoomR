#include "Framebuffer.hpp"

#include <algorithm>
#include <cassert>

Framebuffer::Framebuffer(int width, int height)
    : m_width(width), m_height(height), m_pixels(static_cast<size_t>(width) * height, {16, 16, 16, 255}) {}

void Framebuffer::setPixel(int x, int y, const Color& color) {
    assert(x >= 0 && x < m_width && y >= 0 && y < m_height);
    m_pixels[index(x, y)] = color;
}

Color Framebuffer::getPixel(int x, int y) {
    assert(x >= 0 && x < m_width && y >= 0 && y < m_height);
    return m_pixels[index(x, y)];
}

void Framebuffer::setColumn(int x, int yStart, int yEnd, const Color& color) {
    assert(x >= 0 && x < m_width);
    assert(yStart >= 0 && yStart <= yEnd && yStart < m_height && yEnd >= 0 && yEnd < m_height);

    for (int y = yStart; y <= yEnd; ++y) {
        m_pixels[index(x, y)] = color;
    }
}

void Framebuffer::clear(const Color& color) { std::fill(m_pixels.begin(), m_pixels.end(), color); }