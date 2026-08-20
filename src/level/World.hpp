#pragma once

#include <memory>

#include "Map.hpp"
#include "Player.hpp"

struct InputState;

class World {
   public:
    World(std::unique_ptr<Map> map);

    void update(const InputState& input, float dt);

    [[nodiscard]] const Map* map() const { return m_map.get(); }
    [[nodiscard]] const Player* player() const { return m_player.get(); }

   private:
    std::unique_ptr<Map> m_map;
    std::unique_ptr<Player> m_player;
};