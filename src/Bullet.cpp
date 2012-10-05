#include "Bullet.h"
Bullet::Bullet() {
    setPosition(100,100);
    setDirection(NORTH);
    setHealth(1);
    setMovementRate(10);
    setWidth(5);
    setHeight(5);
    setDamage(10);
    setColor(sf::Color(0,0,0));
}

void Bullet::fire(Direction d) {
    move(d);
}
void Bullet::createShape() {
    shape.setSize(sf::Vector2f(getWidth(), getHeight()));
    shape.setFillColor(getColor());
    shape.setPosition(getX(), getY());

}
