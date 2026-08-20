#pragma once

#include <SDL3/SDL.h>

#include <vector>

#include "render/RenderUtils.hpp"

class Framebuffer;
class Palette;

class Display {
   public:
    Display(SDL_Renderer* renderer, const Framebuffer& fb);
    ~Display();

    void present(const Framebuffer& fb, const Palette& palette);

    [[nodiscard]] const SDL_Texture* texture() const { return m_texture; }

   private:
    SDL_Renderer* m_renderer;
    SDL_Texture* m_texture;
    uint32_t m_width;
    uint32_t m_height;
    std::vector<uint32_t> m_buffer;
};