#include "core/Log.hpp"
#include "platform/Window.hpp"
#include "render/Framebuffer.hpp"
#include "wad/WadFile.hpp"

int main(void) {
    logger::init();
    logger::setLevel(logger::Level::Trace);

    Window window;
    Framebuffer fb(320, 200);

    auto result = WadFile::open("../doom.wad");

    if (!result) {
        LOG_ERROR("Cannot load WAD: {}", toString(result.error()));
        return EXIT_FAILURE;
    }
    auto& wad = *result;

    uint8_t offset = 0;
    while (!window.shouldClose()) {
        window.pollEvents();

        // for (int y = 0; y < fb.height(); ++y) {
        //     for (int x = 0; x < fb.width(); ++x) {
        //         fb.setPixel(x, y, static_cast<uint8_t>(x + offset));
        //     }
        // }
        // offset++;

        window.present(fb);

        SDL_Delay(16);
    }

    return 0;
}