#include "Player.h"

Player::Player() {
    setPosition(0,0);
    setDirection(NORTH);
    setHealth(100);
    setMovementRate(8);
    setWidth(50);
    setHeight(50);
    setDamage(2);
    setColor(sf::Color(240, 0, 0));
}
void Player::createShape() {
    shape.setSize(sf::Vector2f(getWidth(), getHeight()));
    shape.setFillColor(getColor());
    shape.setPosition(getX(), getY());
}
