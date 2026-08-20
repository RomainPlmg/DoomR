#pragma once

#include "core/Math.hpp"

class Player {
   public:
    Player(Vec2 position, angle_t angle);

    void moveForward(fixed_t distance);
    void strafe(fixed_t distance);
    void rotate(angle_t angle);

    const Vec2& position() const { return m_position; }
    const angle_t angle() const { return m_angle; }

   private:
    Vec2 m_position;
    angle_t m_angle;
};