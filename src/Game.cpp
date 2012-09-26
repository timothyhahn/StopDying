
#include "Game.h"

void checkBorderCollision(Entity & e) {
   if(e.getY() < 0)
       e.move(SOUTH);
   if(e.getY() > SCREEN_HEIGHT - e.getHeight())
       e.move(NORTH);
   if(e.getX() < 0)
       e.move(EAST);
   if(e.getX() > SCREEN_WIDTH - e.getWidth())
       e.move(WEST);
}
void checkEntityCollision() {
    if(p.isColliding(eni) || p.isColliding(eni2)) {
        //Lose
    }

    if(eni.isColliding(eni2)) {
        eni.move(eni.flipDirection(eni.getDirection()));
    }
}
void checkInput() {
        Direction d = NONE;
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            d = NORTH;
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
                d = NORTH_WEST;
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
                d = NORTH_EAST;
        } else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            d = SOUTH;
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
                d = SOUTH_WEST;
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
                d = SOUTH_EAST;
        } else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            d = WEST;
        } else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            d = EAST;
        }
        if(d != NONE)
            p.move(d);
}

int Game::initialize() {
    window.create(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32), "Stop Dying!");
    window.setFramerateLimit(60);
    p.setPosition(300,200);
    p.createShape();
    
    eni.createShape();
    
    eni2.setPosition(400, 500);
    eni2.createShape();
    
    start();
}
int Game::start() {

    while(window.isOpen()) {
        sf::Event event;
        while(window.pollEvent(event)) {
            if(event.type == sf::Event::Closed)
                window.close();
        }
    
        checkInput();
        checkBorderCollision(p);
        checkEntityCollision();
        eni.stalkPlayer(p);
        eni2.stalkPlayer(p);
        
        window.clear(sf::Color(0,230,0));
        window.draw(p.shape); 
        window.draw(eni.shape); 
        window.draw(eni2.shape);
        window.display();
    }

}
