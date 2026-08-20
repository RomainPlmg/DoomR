#include "core/Log.hpp"
#include "level/Map.hpp"
#include "level/Player.hpp"
#include "platform/Display.hpp"
#include "platform/Window.hpp"
#include "render/Framebuffer.hpp"
#include "render/MapViewport.hpp"
#include "render/TopDownRenderer.hpp"
#include "wad/Palette.hpp"
#include "wad/WadDirectory.hpp"
#include "wad/WadFile.hpp"

const int MOVE_SPEED = 4;
const angle_t ROT_SPEED = degToAngle(2);

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
    auto palette = Palette::load(*wad, wadDir);  // Extract the color palette 0

    // Create the top-down map viewport
    MapViewport viewport(fb.width(), fb.height(), map->computeBoundingBox());

    // Get player start position and angle
    Vec2 playerPos{};
    angle_t playerAngle;
    for (const auto& t : map->things()) {
        if (t.type == DoomEdThing::Player1StartPos) {
            playerPos = {IntToFixed(t.x), IntToFixed(t.y)};
            playerAngle = degToAngle(t.angle);
            break;
        }
    }

    // Build the player
    Player player(playerPos, playerAngle);

    while (!window.shouldClose()) {
        window.pollEvents();

        const bool* keys = SDL_GetKeyboardState(nullptr);

        if (keys[SDL_SCANCODE_W]) player.moveForward(IntToFixed(MOVE_SPEED));
        if (keys[SDL_SCANCODE_S]) player.moveForward(IntToFixed(-MOVE_SPEED));
        if (keys[SDL_SCANCODE_A]) player.strafe(IntToFixed(MOVE_SPEED));
        if (keys[SDL_SCANCODE_D]) player.strafe(IntToFixed(-MOVE_SPEED));
        if (keys[SDL_SCANCODE_LEFT]) player.rotate(ROT_SPEED);
        if (keys[SDL_SCANCODE_RIGHT]) player.rotate(-ROT_SPEED);

        // Draw the map
        for (const auto& line : map->linedefs()) {
            Vertex v1 = map->vertexes()[line.startVertex];
            Vertex v2 = map->vertexes()[line.endVertex];

            renderer.drawLine(fb, viewport.worldToScreen({v1.x, v1.y}), viewport.worldToScreen({v2.x, v2.y}), 4);
        }

        // Draw the player
        renderer.drawPoint(
            fb, viewport.worldToScreen({FixedToInt(player.position().x), FixedToInt(player.position().y)}), 251);

        // Print on the screen
        display.present(fb, *palette);

        SDL_Delay(16);
    }

    return 0;
}