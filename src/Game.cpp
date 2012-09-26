#include "Game.h"


int Game::initialize() {
    window.create(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32), "Stop Dying!");
    window.setFramerateLimit(60);
    Player p;
    p.createShape();
      
    while(window.isOpen()) {
        sf::Event event;
        while(window.pollEvent(event)) {
            if(event.type == sf::Event::Closed)
                window.close();
        }


        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
            p.up();
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
            p.down();
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            p.left();
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            p.right();

        window.clear(sf::Color(0,230,0));
        window.draw(p.shape); 
        window.display();
    }
}
int Game::start() {

}
