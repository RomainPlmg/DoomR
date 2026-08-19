#include "TopDownRenderer.hpp"

#include "Framebuffer.hpp"

void TopDownRenderer::drawPoint(Framebuffer& fb, const Point& point, const Color& color) {
    fb.setPixel(point.x, point.y, color);
}

void TopDownRenderer::drawLine(Framebuffer& fb, const Point& p1, const Point& p2, const Color& color) {}
