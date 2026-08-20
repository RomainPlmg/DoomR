#include "Display.hpp"

#include <cassert>

#include "core/Log.hpp"
#include "render/Framebuffer.hpp"

static SDL_FRect computeDestRect(int windowWidth, int windowHeight, int textureWidth, int textureHeight) {
    const float windowAspect = static_cast<float>(windowWidth) / windowHeight;
    const float textureAspect = static_cast<float>(textureWidth) / textureHeight;

    SDL_FRect dest;

    if (windowAspect > textureAspect) {
        dest.h = static_cast<float>(windowHeight);
        dest.w = dest.h * textureAspect;
        dest.x = (windowWidth - dest.w) * 0.5f;
        dest.y = 0.0f;
    } else {
        dest.w = static_cast<float>(windowWidth);
        dest.h = dest.w / textureAspect;
        dest.x = 0.0f;
        dest.y = (windowHeight - dest.h) * 0.5f;
    }

    return dest;
}

Display::Display(SDL_Renderer* renderer, const Framebuffer& fb)
    : m_renderer(renderer), m_width(fb.width()), m_height(fb.height()) {
    assert(m_renderer);

    // RGBA format in little endian -> ABGR format
    m_texture = SDL_CreateTexture(m_renderer, SDL_PIXELFORMAT_ABGR8888, SDL_TEXTUREACCESS_STREAMING, m_width, m_height);
    if (!m_texture) {
        LOG_FATAL("{}", SDL_GetError());
        std::abort();
    }
    SDL_SetTextureScaleMode(m_texture, SDL_SCALEMODE_NEAREST);

    m_buffer.resize(m_width * m_height);
}

Display::~Display() {
    if (m_texture) SDL_DestroyTexture(m_texture);
}

void Display::present(const Framebuffer& fb, const Palette& palette) {
    auto pixels = fb.data();

    for (size_t i = 0; i < pixels.size(); ++i) {
        auto v = pixels[i];
        Color c{v, v, v, 255};  // TODO: Real palette
        m_buffer[i] = std::bit_cast<uint32_t>(c);
    }

    SDL_UpdateTexture(m_texture, nullptr, m_buffer.data(), m_width * sizeof(uint32_t));

    int windowW, windowH;
    SDL_GetRenderOutputSize(m_renderer, &windowW, &windowH);
    SDL_FRect dest = computeDestRect(windowW, windowH, m_width, m_height);

    SDL_RenderClear(m_renderer);
    SDL_RenderTexture(m_renderer, m_texture, nullptr, &dest);
    SDL_RenderPresent(m_renderer);
}
