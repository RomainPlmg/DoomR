#include "Window.hpp"

#include <cstdlib>

#include "core/Log.hpp"
#include "render/Framebuffer.hpp"

Window::Window(const WindowProperties& props) {
    m_window = SDL_CreateWindow(props.title.c_str(), props.width * props.scale, props.height * props.scale,
                                SDL_WINDOW_RESIZABLE | SDL_WINDOW_HIGH_PIXEL_DENSITY);
    if (!m_window) {
        LOG_FATAL("{}", SDL_GetError());
        std::abort();
    }

    m_renderer = SDL_CreateRenderer(m_window, nullptr);
    if (!m_renderer) {
        LOG_FATAL("{}", SDL_GetError());
        std::abort();
    }

    m_texture =
        SDL_CreateTexture(m_renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, props.width, props.height);
    if (!m_texture) {
        LOG_FATAL("{}", SDL_GetError());
        std::abort();
    }
    SDL_SetTextureScaleMode(m_texture, SDL_SCALEMODE_NEAREST);

    m_buffer.resize(props.width * props.height);

    LOG_DEBUG("Window init successful!");
}

Window::~Window() {
    if (m_texture) SDL_DestroyTexture(m_texture);
    if (m_renderer) SDL_DestroyRenderer(m_renderer);
    if (m_window) SDL_DestroyWindow(m_window);

    LOG_DEBUG("Window destroy successful!");
}

void Window::pollEvents() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_EVENT_QUIT) m_open = false;
    }
}

void Window::present(const Framebuffer& fb) {
    auto pixels = fb.data();

    for (size_t i = 0; i < pixels.size(); ++i) {
        uint8_t v = pixels[i];
        // TODO: Temporary, color index is grayscale for now
        m_buffer[i] = (v << 24) | (v << 16) | (v << 8) | 0xFF;
    }

    SDL_UpdateTexture(m_texture, nullptr, m_buffer.data(), m_props.width * sizeof(uint32_t));

    SDL_RenderClear(m_renderer);
    SDL_RenderTexture(m_renderer, m_texture, nullptr, nullptr);
    SDL_RenderPresent(m_renderer);
}