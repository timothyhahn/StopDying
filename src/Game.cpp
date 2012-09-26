#include "Game.h"


int Game::initialize() {
    window.create(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32), "Stop Dying!");
    while(window.isOpen()) {
        sf::Event event;
        while(window.pollEvent(event)) {
            if(event.type == sf::Event::Closed)
                window.close();
        }
        Player p;
        p.createShape();
        
        window.clear(sf::Color(0,230,0));
        window.draw(p.shape); 
        window.display();
    }
}
int Game::start() {

}
