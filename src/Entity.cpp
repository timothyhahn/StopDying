#include "Entity.h"
#include <stdio.h>
Entity::Entity() {
    _x = 0;
    _y = 0;
    _direction = NORTH;
    _health = 1;
    _damage = 0;
    _movement_rate = 10;
    _width = 1;
    _height =1;
}
Entity::~Entity() {
}
void Entity::setPosition(float x, float y) {
    _x = x;
    _y = y;
    shape.setPosition(_x, _y);
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

void Entity::setDamage(int damage) {
    _damage = damage;
}

int Entity::getDamage() {
    return _damage;
}

void Entity::createShape() {
    shape.setSize(sf::Vector2f(_width, _height));
    shape.setFillColor(sf::Color(0, 0, 0));
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
    else if(direction == NORTH_WEST) {
        _x -= (_movement_rate / 2);
        _y -= (_movement_rate / 2);
    } else if(direction == NORTH_EAST) {
        _x += (_movement_rate / 2);
        _y -= (_movement_rate / 2);
    } else if(direction == SOUTH_WEST) {
        _x -= (_movement_rate / 2);
        _y += (_movement_rate / 2);
    } else if(direction == SOUTH_EAST) {
        _x += (_movement_rate / 2);
        _y += (_movement_rate / 2);
    }

    _direction = direction;
    shape.setPosition(_x, _y);
}
Direction Entity::flipDirection(Direction direction) {
        if(direction == NORTH)
            return SOUTH;
        else if (direction == SOUTH)
            return NORTH;
        else if (direction == WEST)
            return EAST;
        else if (direction == EAST)
            return WEST;
        else if (direction == NORTH_WEST)
            return SOUTH_EAST;
        else if (direction == SOUTH_EAST)
            return NORTH_WEST;
        else if (direction == NORTH_EAST)
            return SOUTH_WEST;
        else if (direction == SOUTH_WEST)
            return NORTH_EAST;
        else
            return NONE;
}
bool Entity::isColliding(Entity e) {
    bool xOverlap = false;
    bool yOverlap = false;

    // Check X axis collision

    // Grab the x axes for both this and e
    float thisXCoord [2] = {getX(), getX() + getWidth()};
    float eXCoord [2] = {e.getX(), e.getX() + e.getWidth()};

    // Determine leftmost shape
    bool isThisLeftmost;
    if(thisXCoord[0] < eXCoord[0])
        isThisLeftmost = true;
    else
        isThisLeftmost = false;
    if(isThisLeftmost) {
        if((eXCoord[0] - thisXCoord[1]) <= 0)
            xOverlap = true;
    } else {
        if((thisXCoord[0] - eXCoord[1]) <= 0)
            xOverlap = true;
    }
    // Check Y axis collision

    // Grab the Y axes for both this and e
    float thisYCoord [2] = {getY(), getY() + getHeight()};
    float eYCoord [2] = {e.getY(), e.getY() + e.getHeight()};

    // Determine upmost shape
    bool isThisUpmost;
    if(thisYCoord[0] < eYCoord[0])
        isThisUpmost = true;
    else
        isThisUpmost = false;
    if(isThisUpmost) {
        if((eYCoord[0] - thisYCoord[1]) <= 0)
            yOverlap = true;
    } else {
        if((thisYCoord[0] - eYCoord[1]) <= 0)
            yOverlap = true;
    }


    return (xOverlap && yOverlap);
}

void Entity::damage(Entity & e) {
    _health -= e.getDamage();
    //printf("Health: %d \n Damage: %d \n", _health, e.getDamage());
}

