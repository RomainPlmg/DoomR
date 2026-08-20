#include "World.hpp"

#include "core/Angle.hpp"
#include "platform/Input.hpp"

constexpr int MOVE_SPEED = 200;
constexpr angle_t ROT_SPEED = degToAngle(8);

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
    if (input.forward) m_player->moveForward(IntToFixed(MOVE_SPEED * dt));
    if (input.backward) m_player->moveForward(IntToFixed(-MOVE_SPEED * dt));
    if (input.strafeLeft) m_player->strafe(IntToFixed(-MOVE_SPEED * dt));
    if (input.strafeRight) m_player->strafe(IntToFixed(MOVE_SPEED * dt));
    if (input.turnLeft) m_player->rotate(static_cast<angle_t>(ROT_SPEED * dt));
    if (input.turnRight) m_player->rotate(-static_cast<angle_t>(ROT_SPEED * dt));
}