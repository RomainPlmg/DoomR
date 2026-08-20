#pragma once

#include "RenderUtils.hpp"

class Framebuffer;

class TopDownRenderer {
   public:
    void drawPoint(Framebuffer& fb, const Point& point, uint8_t colorIdx);
    void drawLine(Framebuffer& fb, const Point& p1, const Point& p2, uint8_t colorIdx);

   private:
};