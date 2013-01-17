#include "Player.h"

Player::Player() {
    setPosition(0,0);
    setDirection(NORTH);
    setHealth(100);
    setMovementRate(10);
    setWidth(50);
    setHeight(50);
    setDamage(2);
    setColor(sf::Color(240, 0, 0));
    _sword = new Sword();
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

Sword * Player::getSword() {
    return _sword;
}

void Player::shoot() {
    if(_bullets.size() < 30) {
        Bullet * b = new Bullet();
        b->createShape(); 
        b->setDirection(getDirection());
        
        // Determine where on the player you need to "start" the bullet
        int bX = getX();
        int bY = getY();

        // Anything that is "+= 0" is not changed, but has a comment left in to remind you
        Direction d = getDirection();
        if(d == NORTH) {
            bX += (getWidth() / 2);
            // bY += 0;
        } else if (d == SOUTH) {
            bX += (getWidth() / 2);
            bY += getHeight();
        } else if (d == WEST) {
            // bX += 0;
            bY += (getHeight() / 2);
        } else if (d == EAST) {
            bX += getWidth();
            bY += (getHeight() / 2);
        } else if (d == NORTH_WEST) {
            // bX += 0;
            // bY += 0;
        } else if (d == NORTH_EAST) {
            bX += getWidth();
            // bY += 0;
        } else if (d == SOUTH_WEST) {
            // bX += 0;
            bY += getHeight();
        } else if (d == SOUTH_EAST) {
            bX += getHeight();
            bY += getWidth();
        }


        b->setPosition(bX, bY);
        _bullets.push_back(b);
    } 
}

void Player::swing() {
    if(!_sword->isSwung()) {

        Direction d = getDirection();
        float x,y,angle = 0;

        if(d == NORTH) {
            angle = 135;
        } else if (d == SOUTH) {
            angle = 315;
        } else if (d == WEST) {
            angle =  45;
        } else if (d == EAST) {
            angle = 225;
        } else if (d == NORTH_WEST) {
            angle = 90;
        } else if (d == NORTH_EAST) {
            angle = 180;
        } else if (d == SOUTH_WEST) {
            angle = 0;
        } else if (d == SOUTH_EAST) {
            angle = 270;
        }
        x = getX() + (getWidth() / 2);
        y = getY() + (getHeight() / 2);
        //_sword->setDirection(d);
        _sword->setPosition(x,y);
        _sword->setStartAngle(angle);
        _sword->setSwung(true);
    } 
}
