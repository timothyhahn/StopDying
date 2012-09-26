#include "Entity.h"

Entity::Entity() {
    _x = 0;
    _y = 0;
    _direction = NORTH;
    _health = 100;
}

void Entity::setPosition(float x, float y) {
    _x = x;
    _y = y;
}

float Entity::getX() {
    return _x;
}

float Entity::getY() {
    return _y;
}

void Entity::setDirection(Direction direction) {
    _direction = direction;
}

Direction Entity::getDirection() {
    return _direction;
}

void Entity::setHealth(int health) {
    _health = health;
}

int Entity::getHealth() {
    return _health;
}

void Entity::createShape() {
    shape.setSize(sf::Vector2f(50, 50));
    shape.setFillColor(sf::Color(240, 0, 0));
    shape.setPosition(_x, _y);

}
