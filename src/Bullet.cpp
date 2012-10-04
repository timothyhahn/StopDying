#include "Bullet.h"
Bullet::Bullet() {
    setPosition(0,0);
    setDirection(NORTH);
    setHealth(10);
    setMovementRate(5);
    setWidth(20);
    setHeight(20);
    setDamage(10);
    setColor(sf::Color(0,0,220));
}

void Bullet::fire(Direction d) {
    move(d);
}
void Bullet::createShape() {
    shape.setSize(sf::Vector2f(getWidth(), getHeight()));
    shape.setFillColor(getColor());
    shape.setPosition(getX(), getY());

}
