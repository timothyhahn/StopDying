
#include "Game.h"

void moveEnemy(Entity & e) { //How very temporary...
    int yDifference = p.getY() - e.getY();
    int xDifference = p.getX() - e.getX();
    if(abs(yDifference) > abs(xDifference)) { //Move the closer one
        if(yDifference < 0)  //E moves NORTH
            e.move(NORTH);
        else if(yDifference > 0)
            e.move(SOUTH);
    } else {
        if(xDifference < 0)
            e.move(WEST);
        else if (xDifference > 0)
            e.move(EAST);
    }
}
void checkCollision(Entity & e) {
   if(e.getY() < 0)
       e.move(SOUTH);
   if(e.getY() > SCREEN_HEIGHT - e.getHeight())
       e.move(NORTH);
   if(e.getX() < 0)
       e.move(EAST);
   if(e.getX() > SCREEN_WIDTH - e.getWidth())
       e.move(WEST);
}

int Game::initialize() {
    window.create(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32), "Stop Dying!");
    window.setFramerateLimit(60);
    p.setPosition(300,200);
    p.createShape();
    
    eni.setWidth(20);
    eni.setHeight(20);
    eni.createShape();
    eni.shape.setFillColor(sf::Color(0,0,220));
    eni.setMovementRate(5);
    
    eni2.setWidth(20);
    eni2.setHeight(20);
    eni2.setPosition(400, 500);
    eni2.createShape();
    eni2.shape.setFillColor(sf::Color(0,0,220));
    eni2.setMovementRate(5);

    while(window.isOpen()) {
        sf::Event event;
        while(window.pollEvent(event)) {
            if(event.type == sf::Event::Closed)
                window.close();
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
            p.move(NORTH);
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
            p.move(SOUTH);
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            p.move(WEST);
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            p.move(EAST);
        
        checkCollision(p);
        moveEnemy(eni);
        moveEnemy(eni2);

        window.clear(sf::Color(0,230,0));
        window.draw(p.shape); 
        window.draw(eni.shape); 
        window.draw(eni2.shape);
        window.display();
    }
}
int Game::start() {

}
