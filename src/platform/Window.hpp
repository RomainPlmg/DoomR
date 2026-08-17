#pragma once

#include <SDL3/SDL.h>

#include <cstdint>
#include <string>
#include <vector>

class Framebuffer;

struct WindowProperties {
    uint32_t width = 320;
    uint32_t height = 200;
    uint8_t scale = 4;
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
    void present(const Framebuffer& fb);

    [[nodiscard]] bool shouldClose() const { return !m_open; }
    [[nodiscard]] SDL_Window* window() const { return m_window; }

   private:
    SDL_Window* m_window = nullptr;
    SDL_Renderer* m_renderer = nullptr;
    SDL_Texture* m_texture = nullptr;
    WindowProperties m_props;
    bool m_open = true;

    std::vector<uint32_t> m_buffer;
};