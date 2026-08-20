#include "core/Fixed.hpp"
#include "core/Log.hpp"
#include "core/Math.hpp"
#include "level/World.hpp"
#include "platform/Display.hpp"
#include "platform/Input.hpp"
#include "platform/Window.hpp"
#include "render/Framebuffer.hpp"
#include "render/MapViewport.hpp"
#include "render/TopDownRenderer.hpp"
#include "wad/Palette.hpp"

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
    Input input;

    // Open the WAD file
    auto result = WadFile::open("../Doom-ud.wad");
    if (!result) {
        LOG_ERROR("Cannot load WAD: {}", toString(result.error()));
        return EXIT_FAILURE;
    }
    auto& wad = *result;

    // Parse the WAD & read the map E1M1
    WadDirectory wadDir(*wad);
    auto map = Map::load(*wad, wadDir, "E1M1");
    World world(std::move(map));

    // Extract the color palette 0
    auto palette = Palette::load(*wad, wadDir);

    // Create the top-down map viewport
    MapViewport viewport(fb.width(), fb.height(), world.map()->computeBoundingBox());

    while (!window.shouldClose()) {
        window.pollEvents();

        world.update(input.poll(), 0.f);

        fb.clear();

        // Draw the map
        for (const auto& line : world.map()->linedefs()) {
            Vertex v1 = world.map()->vertexes()[line.startVertex];
            Vertex v2 = world.map()->vertexes()[line.endVertex];

            renderer.drawLine(fb, viewport.worldToScreen({v1.x, v1.y}), viewport.worldToScreen({v2.x, v2.y}), 4);
        }

        // Draw the player
        Point dirPoint = {
            FixedToInt(world.player()->position().x +
                       FixedMul(angleCos(world.player()->angle() + ANG90), IntToFixed(128))),
            FixedToInt(world.player()->position().y +
                       FixedMul(angleSin(world.player()->angle() + ANG90), IntToFixed(128))),
        };

        renderer.drawLine(fb,
                          viewport.worldToScreen(
                              {FixedToInt(world.player()->position().x), FixedToInt(world.player()->position().y)}),
                          viewport.worldToScreen({dirPoint.x, dirPoint.y}), 251);

        renderer.drawFilledCircle(fb,
                                  viewport.worldToScreen({FixedToInt(world.player()->position().x),
                                                          FixedToInt(world.player()->position().y)}),
                                  4, 251);

        // Print on the screen
        display.present(fb, *palette);

        SDL_Delay(16);
    }

    return 0;
}