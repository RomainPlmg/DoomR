#pragma once

#include <array>
#include <memory>

#include "render/RenderUtils.hpp"
#include "wad/WadDirectory.hpp"
#include "wad/WadFile.hpp"

class Palette {
   public:
    static std::unique_ptr<Palette> load(const WadFile& file, const WadDirectory& dir, uint8_t paletteIdx = 0);

    [[nodiscard]] Color colorAt(uint8_t colorIndex) const noexcept { return m_colors[colorIndex]; }

   private:
    Palette() = default;

    std::array<Color, 256> m_colors;
};