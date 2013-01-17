#include "Sword.h"
Sword::Sword() {
    setPosition(100,100);
    setDirection(NORTH);
    setHealth(1000);
    setMovementRate(10);
    setWidth(10);
    setHeight(90);
    setDamage(3);
    setColor(sf::Color(0,0,0));
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

void Sword::setStartAngle(float startAngle) {
    _angle = startAngle;
    _startAngle = startAngle;  
    _finalAngle = startAngle + 90.0f;  
}

void Sword::swing() {
    _angle += 9.0f;


    if(_angle > _finalAngle) {
        _angle = _startAngle;
        _swung = false;
    }

    shape.setPosition(getX(), getY());
    shape.setRotation(_angle);
}

void Sword::createShape() {
    shape.setSize(sf::Vector2f(getWidth(), getHeight()));
    shape.setFillColor(getColor());
    shape.setPosition(getX(), getY());
    _angle = 0;
}

bool Sword::swordColliding(Entity e) {
    bool xOverlap = false;
    bool yOverlap = false;

    // Check X axis collision

    // Grab the x axes for both this and e
    float thisXCoord [2] = {shape.getGlobalBounds().left, shape.getGlobalBounds().left + shape.getGlobalBounds().width};
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
    float thisYCoord [2] = {shape.getGlobalBounds().top, shape.getGlobalBounds().top + shape.getGlobalBounds().height};
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