#include "Player.h"

Player::Player() {
    setPosition(0,0);
    setDirection(NORTH);
    setHealth(100);
    setMovementRate(8);
    setWidth(50);
    setHeight(50);
    setDamage(2);
    setColor(sf::Color(240, 0, 0));
}

void Player::createShape() {
    shape.setSize(sf::Vector2f(getWidth(), getHeight()));
    shape.setFillColor(getColor());
    shape.setPosition(getX(), getY());
}

std::vector<Bullet*> Player::getBullets() {
    return _bullets;
}

void Player::setBullets(std::vector<Bullet*> bullets) {
    _bullets = bullets;
}

void Player::shoot() {
    if(_bullets.size() < 30) {
        Bullet * b = new Bullet();
        b->createShape(); 
        b->setDirection(getDirection());
        b->setPosition(getX() + getWidth(), getY() + getHeight());
        _bullets.push_back(b);
    } 
}
