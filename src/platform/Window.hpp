#pragma once

#include <SDL3/SDL.h>

#include <cstdint>
#include <string>
#include <vector>

class Framebuffer;

struct WindowProperties {
    uint32_t width = 1280;
    uint32_t height = 720;
    std::string title = "DOOM";
};

class Window {
   public:
    Window(const WindowProperties& props = {});
    ~Window();

    Window(const Window&) = delete;
    Window& operator=(const Window&) = delete;
    Window(Window&&) = delete;
    Window& operator=(Window&&) = delete;

    void pollEvents();

    [[nodiscard]] bool shouldClose() const { return !m_open; }
    [[nodiscard]] SDL_Window* window() const { return m_window; }
    [[nodiscard]] SDL_Renderer* renderer() const { return m_renderer; }

   private:
    SDL_Window* m_window = nullptr;
    SDL_Renderer* m_renderer = nullptr;
    WindowProperties m_props;
    bool m_open = true;

    std::vector<uint32_t> m_buffer;
};