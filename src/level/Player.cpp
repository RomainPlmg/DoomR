#include "Player.hpp"

Player::Player(Vec2 position, angle_t angle) : m_position(position), m_angle(angle) {}

void Player::moveForward(fixed_t distance) {
    m_position.x += FixedMul(angleCos(m_angle + ANG90), distance);
    m_position.y += FixedMul(angleSin(m_angle + ANG90), distance);
}

void Player::strafe(fixed_t distance) {
    m_position.x += FixedMul(angleCos(m_angle), distance);
    m_position.y += FixedMul(angleSin(m_angle), distance);
}

void Player::rotate(angle_t angle) { m_angle += angle; }