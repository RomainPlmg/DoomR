#include "World.hpp"

#include "platform/Input.hpp"

constexpr int MOVE_SPEED = 4;
constexpr angle_t ROT_SPEED = degToAngle(0.3);

World::World(std::unique_ptr<Map> map) : m_map(std::move(map)) {
    // Get player start position and angle
    Vec2 playerPos{};
    angle_t playerAngle;
    for (const auto& t : m_map->things()) {
        if (t.type == DoomEdThing::Player1StartPos) {
            playerPos = {IntToFixed(t.x), IntToFixed(t.y)};
            playerAngle = degToAngle(t.angle);
            break;
        }
    }

    m_player = std::make_unique<Player>(playerPos, playerAngle);
}

void World::update(const InputState& input, float dt) {
    if (input.forward) m_player->moveForward(IntToFixed(MOVE_SPEED));
    if (input.backward) m_player->moveForward(IntToFixed(-MOVE_SPEED));
    if (input.strafeLeft) m_player->strafe(IntToFixed(-MOVE_SPEED));
    if (input.strafeRight) m_player->strafe(IntToFixed(MOVE_SPEED));
    if (input.turnLeft) m_player->rotate(ANG1 * 2);
    if (input.turnRight) m_player->rotate(-(ANG1 * 2));
}