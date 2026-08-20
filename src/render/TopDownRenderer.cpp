#include "TopDownRenderer.hpp"

#include <cmath>

#include "Framebuffer.hpp"

void TopDownRenderer::drawPoint(Framebuffer& fb, const Point& point, uint8_t colorIdx) {
    fb.setPixel(point.x, point.y, colorIdx);
}

void TopDownRenderer::drawLine(Framebuffer& fb, const Point& p1, const Point& p2, uint8_t colorIdx) {
    // DDA algorithm
    int dx = p2.x - p1.x;
    int dy = p2.y - p1.y;

    // Get number of steps
    int steps = std::max(std::abs(dx), std::abs(dy));

    float xIncr = static_cast<float>(dx) / steps;
    float yIncr = static_cast<float>(dy) / steps;

    // Init start position
    float x = p1.x;
    float y = p1.y;

    for (int i = 0; i < steps; i++) {
        int xRounded = static_cast<int>(std::round(x));
        int yRounded = static_cast<int>(std::round(y));

        fb.setPixel(xRounded, yRounded, colorIdx);

        x += xIncr;
        y += yIncr;
    }
}

void TopDownRenderer::drawFilledCircle(Framebuffer& fb, const Point& center, int radius, uint8_t colorIdx) {
    for (int32_t y = -radius; y <= radius; ++y) {
        for (int32_t x = -radius; x <= radius; ++x) {
            if (x * x + y * y <= radius * radius) {
                drawPoint(fb, {center.x + x, center.y + y}, colorIdx);
            }
        }
    }
}
