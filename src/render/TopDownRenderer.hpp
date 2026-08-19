#pragma once

#include "RenderUtils.hpp"

class Framebuffer;

class TopDownRenderer {
   public:
    void drawPoint(Framebuffer& fb, const Point& point, const Color& color);
    void drawLine(Framebuffer& fb, const Point& p1, const Point& p2, const Color& color);

   private:
};