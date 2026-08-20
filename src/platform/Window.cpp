#include "Window.hpp"

#include <cassert>
#include <cstdlib>

#include "core/Log.hpp"

Window::Window(const WindowProperties& props) {
    m_window = SDL_CreateWindow(props.title.c_str(), props.width, props.height,
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

    LOG_DEBUG("Window init successful!");
}

Window::~Window() {
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