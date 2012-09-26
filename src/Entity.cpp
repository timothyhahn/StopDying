#include "Entity.h"

Entity::Entity() {
    _x = 0;
    _y = 0;
    _direction = NORTH;
    _health = 100;
    _movement_rate = 10;
    _width = 50;
    _height = 50;
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

void Entity::setWidth(int width) {
    _width = width;
}

int Entity::getWidth() {
    return _width;
}

void Entity::setHeight(int height) {
    _height = height;
}

int Entity::getHeight() {
    return _height;
}

void Entity::setMovementRate(int movement_rate) {
    _movement_rate = movement_rate;
}

int Entity::getMovementRate() {
    return _movement_rate;
}

void Entity::createShape() {
    shape.setSize(sf::Vector2f(_width, _height));
    shape.setFillColor(sf::Color(240, 0, 0));
    shape.setPosition(_x, _y);
}
void Entity::move(Direction direction) {
    if(direction == NORTH)
        _y -= _movement_rate;
    else if(direction == SOUTH)
        _y += _movement_rate;
    else if(direction == WEST)
        _x -= _movement_rate;
    else if(direction == EAST)
        _x += _movement_rate;

    _direction = direction;
    shape.setPosition(_x, _y);
}
