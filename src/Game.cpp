
#include "Game.h"

Enemy eni3;

void centerEntity(Entity & e) {
    e.setPosition((SCREEN_WIDTH / 2) - (e.getWidth() / 2), (SCREEN_HEIGHT / 2) - (e.getHeight() / 2));
    e.shape.setPosition(e.getX(), e.getY());
}

void randomPositionEntity(Entity & e) {
    centerEntity(e);

    int north_or_south = rand() % 2 + 1; // 1 = NORTH, 2 = SOUTH
    int west_or_east = rand() % 2 + 1; // 1 = WEST, 2 = EAST

    int maxXOffset = (SCREEN_WIDTH - e.getWidth()) / 2;
    int minXOffset = maxXOffset / 4;
    maxXOffset -= minXOffset;
    int xOffset = rand() % maxXOffset + minXOffset;

    int maxYOffset = (SCREEN_HEIGHT - e.getHeight()) / 2;
    int minYOffset = maxYOffset / 4;
    maxYOffset -= minYOffset;
    int yOffset = rand() & maxYOffset + minYOffset;

    if(north_or_south == 1)
        yOffset = -yOffset;
    if(west_or_east == 1)
        xOffset = -xOffset;

    e.setPosition(e.getX() + xOffset, e.getY() + yOffset);

}

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
    //if(p.isColliding(eni) || p.isColliding(eni2)) {
        //Lose
   // }

   // if(eni.isColliding(eni2)) {
    //    eni.move(eni.flipDirection(eni.getDirection()));
   // }
}
void checkDeath() {
    if(p.getHealth() < 1) {
        game_running = false;
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
    enemies.push_back(new Enemy);
    enemies.push_back(new Enemy);

    srand(time(NULL));
    setupEntities();
    game_over = false;
    while(!game_over){
        start();
    }
    return 0;
}
int Game::setupEntities() {
    srand(time(NULL));

    centerEntity(p);
    p.createShape();


    for(std::vector<Enemy*>::iterator iter  = enemies.begin(); iter != enemies.end(); ++iter) {
        Enemy * eni = *iter;
        randomPositionEntity(*eni);
        eni->createShape();
    }

}
int Game::start() {
    game_running = true;
    while(window.isOpen()) {
        while(game_running) {
            sf::Event event;

            while(window.pollEvent(event)) {
                if(event.type == sf::Event::Closed)
                    window.close();
            }

            checkInput();
            checkBorderCollision(p);
            checkEntityCollision();
            for(std::vector<Enemy*>::iterator iter  = enemies.begin(); iter != enemies.end(); ++iter) {
                Enemy *eni = *iter;
                eni->stalkPlayer(p);
            }
            window.clear(sf::Color(0,230,0));
            window.draw(p.shape);
            for(std::vector<Enemy*>::iterator iter  = enemies.begin(); iter != enemies.end(); ++iter) {
                Enemy *eni = *iter;
                window.draw(eni->shape);
            }
            window.display();
        }
        setupEntities();
        game_running = true;
    }
    return 0;
}
