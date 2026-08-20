#include "TopDownRenderer.hpp"

#include "Framebuffer.hpp"

void TopDownRenderer::drawPoint(Framebuffer& fb, const Point& point, uint8_t colorIdx) {
    fb.setPixel(point.x, point.y, colorIdx);
}

void TopDownRenderer::drawLine(Framebuffer& fb, const Point& p1, const Point& p2, uint8_t colorIdx) {}
