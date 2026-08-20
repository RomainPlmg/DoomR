#include "Palette.hpp"

#include "core/Log.hpp"

std::unique_ptr<Palette> Palette::load(const WadFile& file, const WadDirectory& dir, uint8_t paletteIdx) {
    auto entry = dir.find("PLAYPAL");

    if (!entry) {
        LOG_ERROR("Unable to find the palette entry PLAYPAL.");
        return nullptr;
    }

    std::unique_ptr<Palette> palette(new Palette());

    auto data = file.readLump(*entry);

    for (size_t i = 0; i < palette->m_colors.size(); i++) {
        auto& color = palette->m_colors[i];
        color.r = static_cast<uint8_t>(data[i * 3]);
        color.g = static_cast<uint8_t>(data[i * 3 + 1]);
        color.b = static_cast<uint8_t>(data[i * 3 + 2]);
    }

    return palette;
}
