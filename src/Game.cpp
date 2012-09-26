#include "Game.h"

void checkCollision(Entity e) {
   if(p.getY() < 0)
       p.move(SOUTH);
   if(p.getY() > SCREEN_HEIGHT - p.getHeight())
       p.move(NORTH);
   if(p.getX() < 0)
       p.move(EAST);
   if(p.getX() > SCREEN_WIDTH - p.getWidth())
       p.move(WEST);
}

int Game::initialize() {
    window.create(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32), "Stop Dying!");
    window.setFramerateLimit(60);
    p.createShape();
      
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


        window.clear(sf::Color(0,230,0));
        window.draw(p.shape); 
        window.display();
    }
}
int Game::start() {

}
