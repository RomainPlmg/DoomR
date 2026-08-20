#include "core/Log.hpp"
#include "level/Map.hpp"
#include "platform/Display.hpp"
#include "platform/Window.hpp"
#include "render/Framebuffer.hpp"
#include "render/MapViewport.hpp"
#include "render/TopDownRenderer.hpp"
#include "wad/Palette.hpp"
#include "wad/WadDirectory.hpp"
#include "wad/WadFile.hpp"

int main(void) {
    // Init logger
    logger::init();
    logger::setLevel(logger::Level::Trace);

    // Create window, framebuffer and renderer
    WindowProperties props{};
    props.width = 1280;
    props.height = 720;

    Window window(props);
    Framebuffer fb(800, 600);
    TopDownRenderer renderer;
    Display display(window.renderer(), fb);

    // Open the WAD file
    auto result = WadFile::open("../doom.wad");
    if (!result) {
        LOG_ERROR("Cannot load WAD: {}", toString(result.error()));
        return EXIT_FAILURE;
    }
    auto& wad = *result;

    // Parse the WAD & read the map E1M1
    WadDirectory wadDir(*wad);
    auto map = Map::load(*wad, wadDir, "E1M1");

    MapViewport viewport(fb.width(), fb.height(), map->computeBoundingBox());

    Palette p;

    uint8_t offset = 0;
    while (!window.shouldClose()) {
        window.pollEvents();

        for (const auto& v : map->vertexes()) {
            renderer.drawPoint(fb, viewport.worldToScreen({v.x, v.y}), 255);
        }
        offset++;

        display.present(fb, p);

        SDL_Delay(16);
    }

    return 0;
}