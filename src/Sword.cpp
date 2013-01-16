#include "Sword.h"
Sword::Sword() {
    setPosition(100,100);
    setDirection(NORTH);
    setHealth(1000);
    setMovementRate(10);
    setWidth(10);
    setHeight(90);
    setDamage(10);
    setColor(sf::Color(0,0,0));
    _angle = 0.0f;
    _swung = false;
}

bool Sword::isSwung() {
    return _swung;
}

void Sword::setSwung(bool swung) {
    _swung = swung;
}
float Sword::getAngle() {
    return _angle;
}
void Sword::swing() {
    _angle += 9.0f;

    float angle_start = 0;
    float angle_max = 90;

    if(_angle > 90) {
        _angle = 0.0f;
        _swung = false;
    }

    shape.setPosition(getX(), getY());
    shape.setRotation(_angle);
}

void Sword::createShape() {
    shape.setSize(sf::Vector2f(getWidth(), getHeight()));
    shape.setFillColor(getColor());
    shape.setPosition(getX(), getY());
}
