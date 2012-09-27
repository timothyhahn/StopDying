#include "Enemy.h"

Enemy::Enemy() {
    setPosition(0,0);
    setDirection(NORTH);
    setHealth(10);
    setMovementRate(5);
    setWidth(20);
    setHeight(20);
}
void Enemy::stalkPlayer(Player p) {
    int yDifference = p.getY() - getY();
    int xDifference = p.getX() - getX();
    if(abs(yDifference) > abs(xDifference)) { //Move the farther one
        if(yDifference < 0)  //E moves NORTH
            move(NORTH);
        else if(yDifference > 0)
            move(SOUTH);
    } else {
        if(xDifference < 0)
            move(WEST);
        else if (xDifference > 0)
            move(EAST);
    }
}
void Enemy::createShape() {
    shape.setSize(sf::Vector2f(getWidth(), getHeight()));
    shape.setFillColor(sf::Color(0, 0, 220));
    shape.setPosition(getX(), getY());

}
