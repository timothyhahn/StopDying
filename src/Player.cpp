#include "Player.h"

Player::Player() {
    setPosition(0,0);
    setDirection(NORTH);
    setHealth(100);
    setMovementRate(8);
    setWidth(50);
    setHeight(50);
}
void Player::createShape() {
    shape.setSize(sf::Vector2f(getWidth(), getHeight()));
    shape.setFillColor(sf::Color(240, 0, 0));
    shape.setPosition(getX(), getY());
}
