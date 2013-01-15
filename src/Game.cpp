
#include "Game.h"

/**
 * Used to place the player in the middle of the screen in new games and restarts.
 * @param e An entity that needs to move (passed by reference)
 */
void centerEntity(Entity & e) {
   e.setPosition((SCREEN_WIDTH / 2) - (e.getWidth() / 2), (SCREEN_HEIGHT / 2) - (e.getHeight() / 2));
    e.shape.setPosition(e.getX(), e.getY());
}

/**
 * Used to place entities around the player.
 * @ param e An entity that needs to be near the player.
 */
void centerEntityOnPlayer(Entity & e) {
   e.setPosition(p.getX(), p.getY());
    e.shape.setPosition(e.getX(), e.getY());
}

/**
 * We don't want entities to actually be *on* the user, so we find a decent offset
 * for both the X and Y axes, and offset them by that much.
 * @param e An entity that is randomly offset from the player.
 */
void randomPositionEntity(Entity & e) {
    centerEntityOnPlayer(e);

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

/**
 * Makes sure the user doesn't get pushed off/move off the screen. If they do, their
 * position is set to the lowest it should be
 * @param e An entity that is kept from escaping the visible screen.
 */
void checkBorderCollision(Entity & e) {
   if(e.getY() < 0)
       e.setPosition(e.getX(), 0);
   if(e.getY() > SCREEN_HEIGHT - e.getHeight())
       e.setPosition(e.getX(), SCREEN_HEIGHT - e.getHeight());
   if(e.getX() < 0)
       e.setPosition(0, e.getY());
   if(e.getX() > SCREEN_WIDTH - e.getWidth())
       e.setPosition(SCREEN_WIDTH - e.getWidth(), e.getY());
}

/**
 * Handles a numerous amount of collisions that happen in this game.
 * Will detect if the player is colliding with an enemy or a ,
 * or if an enemy is colliding with an enemy or bullet and then respond
 * appropriately
 */
void checkEntityCollision() {
    for(std::vector<Enemy*>::iterator iter  = enemies.begin(); iter != enemies.end(); ++iter) {
        Enemy * eni = *iter;

        // Check if bullets are colliding with enemies
        for(std::vector<Bullet*>::iterator checkAgainst = bullets.begin(); checkAgainst != bullets.end(); ++checkAgainst) {
            Bullet * b = *checkAgainst;
            if(eni->isColliding(*b)) {
                eni->damage(*b);
                b->damage(*eni);
            }
        }
        
        // Check if player is colliding with enemies
        if(p.isColliding(*eni)) {
            Direction moveTo = eni->getDirection();
            p.move(moveTo);
            eni->move(eni->flipDirection(moveTo));
            p.damage(*eni);
            eni->damage(p);
            p.setBlinking(true);
        }

        // Check if enemies are colliding with each other
        for(std::vector<Enemy*>::iterator checkAgainst = enemies.begin(); checkAgainst != enemies.end(); ++checkAgainst) {
            Enemy * next = *checkAgainst;
            Enemy nexter = *next;

            Direction moveTo = eni->flipDirection(eni->getDirection());
            if(eni->isColliding(nexter) && (eni != next)) {
                bool checkOverlap = true;
                    while(checkOverlap) {
                        eni->move(moveTo);
                        if(eni->isColliding(nexter) && (eni != next)) {
                            checkOverlap = true;
                        } else {
                            checkOverlap = false;
                        }
                    }

            }
        }

    }
}

/**
 * Will handle various animations depending on different settings and magics.
 */
void checkAnimations() {
    if(p.isBlinking()) {
        if((p.getBlinkCounter() % 20) < 10) {
            p.shape.setFillColor(sf::Color(0,0,0,0));
        } else {
            p.shape.setFillColor(p.getColor());
        }
        p.setBlinkCounter(p.getBlinkCounter() + 1);
        if(p.getBlinkCounter() > 30) {
            p.setBlinkCounter(0);
            p.setBlinking(false);
            p.shape.setFillColor(p.getColor());
        }

    }
    for(std::vector<Bullet*>::iterator iter = bullets.begin(); iter != bullets.end(); ++iter) {
        Bullet *b = *iter;
        b->fire();
    }

}

/**
 * Will randomly create enemies
 */
void spawnEnemies() {
    float percent_chance = spawn_rate * 10000;

    int random_number = rand() % 10000;
    if(random_number < percent_chance) {
        Enemy * eni = new Enemy;
        randomPositionEntity(*eni);
        eni->createShape();
        enemies.push_back(eni);
    }
}

/**
 * If a player, enemy, or bullet has less than 1 health, it is frigging DEAD
 */
void checkDeath() {
    if(p.getHealth() < 1) {
        game_running = false;
    }
    std::vector<Enemy*>::iterator eIter = enemies.begin();

    while(eIter != enemies.end()) {
        Enemy * eni = *eIter;
        if(eni->getHealth() < 1) {
            eIter = enemies.erase(eIter);
        } else {
            ++eIter;
        }
    }

    std::vector<Bullet*>::iterator bIter = bullets.begin();
    while(bIter != bullets.end()) {
        Bullet * b = *bIter;
        if(b->getHealth() < 1) {
            bIter = bullets.erase(bIter);
            p.setBullets(bullets);
        } else {
            ++bIter;
        }
    }

    // Check to see if a bullet is "off screen, in which case it DIES"
    bIter = bullets.begin();

    while(bIter != bullets.end()) {
        Bullet * b = *bIter;
        if(b->getX() < 0 || b->getX() > SCREEN_WIDTH || b->getY() < 0 || b->getY() > SCREEN_HEIGHT) {
            bIter = bullets.erase(bIter);
            p.setBullets(bullets);
        } else {
            ++bIter;
        }
    }
}

/**
 * Will read user input and react
 */
void checkInput() {
        // Directional inputs
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

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
            p.shoot();
        }
}

/**
 * Sets up the window that will be used and various game settings
 * Should only be run once
 */
int Game::initialize() {
    window.create(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32), "Stop Dying!");
    window.setFramerateLimit(60);
    spawn_rate = 0.01f;
    srand(time(NULL));
    setupEntities();
    game_over = false;
    while(!game_over){
        start();
    }
    return 0;
}

/**
 * Sets up various elements that are repeatable and can be used for restarting a game
 */
int Game::setupEntities() {
    srand(time(NULL));

    p = Player();
    centerEntity(p);
    p.createShape();

    enemies.clear();
    enemies.push_back(new Enemy);

    bullets.clear();

    for(std::vector<Enemy*>::iterator iter  = enemies.begin(); iter != enemies.end(); ++iter) {
        Enemy * eni = *iter;
        randomPositionEntity(*eni);
        eni->createShape();
    }
    return 0;
}

/**
 * Runs the game! WHOO!
 */
int Game::start() {
    game_running = true;
    while(window.isOpen()) {
        while(game_running) {
            sf::Event event;

            while(window.pollEvent(event)) {
                if(event.type == sf::Event::Closed) {
                    window.close();
                    game_running = false;
                    game_over = true;
                }
            }

            bullets = p.getBullets();
            spawnEnemies();
            checkInput();
            checkBorderCollision(p);
            checkEntityCollision();
            checkAnimations();
            checkDeath();


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

            for(std::vector<Bullet*>::iterator iter = bullets.begin(); iter != bullets.end(); ++iter) {
                Bullet *b = *iter;
                window.draw(b->shape);
            }

            window.display();
        }

        setupEntities();
        game_running = true;
    }
    return 0;
}
