#include "Bullet.h"
Bullet::Bullet() {
    setPosition(100,100);
    setDirection(NORTH);
    setHealth(1);
    setMovementRate(10);
    setWidth(10);
    setHeight(10);
    setDamage(10);
    setColor(sf::Color(0,0,0));
}

bool Bullet::isFired() {
    return _fired;
}

void Bullet::setFired(bool fired) {
    _fired = fired;
}
void Bullet::fire() {
    move(getDirection());
}
void Bullet::createShape() {
    shape.setSize(sf::Vector2f(getWidth(), getHeight()));
    shape.setFillColor(getColor());
    shape.setPosition(getX(), getY());

}
