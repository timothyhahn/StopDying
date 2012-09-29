#ifndef ENTITY_H
#define ENTITY_H
#include <SFML/Graphics.hpp>
enum Direction{ NORTH, NORTH_WEST, NORTH_EAST, WEST, EAST, SOUTH, SOUTH_WEST, SOUTH_EAST, NONE };

class Entity {
    private:
        float _x;
        float _y;
        Direction _direction;
        int _health;
        int _damage;
        float _movement_rate;
        int _height;
        int _width;

    public:
        Entity();
        ~Entity();
        void setPosition(float x, float y);
        float getX();
        float getY();
        void setDirection(Direction direction);
        Direction getDirection();
        void setHealth(int health);
        int getHealth();
        void setHeight(int height);
        int getHeight();
        void setWidth(int width);
        int getWidth();
        sf::RectangleShape shape;
        void setMovementRate(int movement_rate);
        int getMovementRate();
        void setDamage(int damage);
        int getDamage();
        virtual void createShape();
        void move(Direction direction);
        bool isColliding(Entity e);
        Direction flipDirection(Direction direction);
        void damage(Entity & e);
};
#endif
