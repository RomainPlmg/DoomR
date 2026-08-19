#include "core/Log.hpp"
#include "level/Map.hpp"
#include "platform/Window.hpp"
#include "render/Framebuffer.hpp"
#include "render/MapViewport.hpp"
#include "render/TopDownRenderer.hpp"
#include "wad/WadDirectory.hpp"
#include "wad/WadFile.hpp"

int main(void) {
    // Init logger
    logger::init();
    logger::setLevel(logger::Level::Trace);

    // Create window, framebuffer and renderer
    Window window;
    Framebuffer fb(320, 200);
    TopDownRenderer renderer;

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

    MapViewport viewport(320, 200, map->computeBoundingBox());

    uint8_t offset = 0;
    while (!window.shouldClose()) {
        window.pollEvents();

        for (const auto& v : map->vertexes()) {
            renderer.drawPoint(fb, viewport.worldToScreen({v.x, v.y}), {255, 0, 0, 255});
        }
        offset++;

        window.present(fb);

        SDL_Delay(16);
    }

    return 0;
}