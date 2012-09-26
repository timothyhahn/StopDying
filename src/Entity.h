#ifndef ENTITY_H
#define ENTITY_H
#include <SFML/Graphics.hpp>

enum Direction{ NORTH, EAST, WEST, SOUTH };

class Entity {
    private:
        float _x;
        float _y;
        Direction _direction;
        int _health;
    public:
        Entity();
        void setPosition(float x, float y);
        float getX();
        float getY();
        void setDirection(Direction direction);
        Direction getDirection(); 
        void setHealth(int health);
        int getHealth();
        sf::RectangleShape shape;
        void createShape();
};
#endif
