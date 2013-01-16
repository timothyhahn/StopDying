
#include "Game.h"

int numDigits(int x) {
    int digits = 0;
    while (x) {
        x /= 10;
        digits++;
    }
    return digits;
}
static inline std::string processScore(int x) { 
    std::stringstream padding;
    for(int i = numDigits(x); i < 7; i++) {
        padding << "0";
    }
    std::stringstream type; 
    type << x; 
    return padding.str() + type.str(); 
}


/**
 * Used to place the player in the middle of the screen in new games and restarts.
 * @param e An entity that needs to move (passed by reference)
 */
void centerEntity(Entity & e) {
   e.setPosition((GAME_WIDTH / 2) - (e.getWidth() / 2), (GAME_HEIGHT / 2) - (e.getHeight() / 2));
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

    int maxXOffset = (GAME_WIDTH - e.getWidth()) / 2;
    int minXOffset = maxXOffset / 1.5;
    maxXOffset -= minXOffset;
    int xOffset = rand() % maxXOffset + minXOffset;

    int maxYOffset = (GAME_HEIGHT - e.getHeight()) / 2;
    int minYOffset = maxYOffset / 1.5;
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
   if(e.getY() > GAME_HEIGHT - e.getHeight())
       e.setPosition(e.getX(), GAME_HEIGHT - e.getHeight());
   if(e.getX() < 0)
       e.setPosition(0, e.getY());
   if(e.getX() > GAME_WIDTH - e.getWidth())
       e.setPosition(GAME_WIDTH - e.getWidth(), e.getY());
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
                score += 50;
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
            sf::SoundBuffer buffer;
            buffer.loadFromFile("hit.wav");

            sf::Sound sound;
            sound.setBuffer(buffer);
            sound.play();
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
        if(b->getX() < 0 || b->getX() > GAME_WIDTH || b->getY() < 0 || b->getY() > GAME_HEIGHT) {
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

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::X)) {
            if(time_since_fire >= SHOOTING_OFFSET){
                p.shoot();
                time_since_fire = 0;
                sf::SoundBuffer buffer;
                buffer.loadFromFile("shoot.wav");

                sf::Sound sound;
                sound.setBuffer(buffer);
                sound.play();
            } 
        }
}

void updateScore() {
    int addToScore = 1;
    addToScore += (enemies.size() * 3);
    if(p.getHealth() < 40) {
        addToScore += 2;
    }
    score += addToScore;
}

void updateInterface() {
    while(!interface.empty()) {
        delete interface.back(), interface.pop_back();
    }
    interface.clear();

    // Background
    sf::RectangleShape * background = new sf::RectangleShape();
    background->setSize(sf::Vector2f(INTERFACE_WIDTH, INTERFACE_HEIGHT));
    background->setFillColor(sf::Color::Black);
    background->setPosition(0, GAME_HEIGHT + 1);
    interface.push_back(background);

    // Columns and Rows
    unsigned int column1Offset = 50;
    unsigned int row1Offset = GAME_HEIGHT + 30; 
    unsigned int column2Offset = (INTERFACE_WIDTH / 2);
    unsigned int row2Offset = GAME_HEIGHT + 70;

    // Health Bar (column 1/2, row 1)
    unsigned int healthBarWidth = INTERFACE_WIDTH - (column1Offset * 2);
    unsigned int healthBarHeight = 30;
    unsigned int healthBarThickness = 5;

    sf::RectangleShape * healthOutline = new sf::RectangleShape();
    healthOutline->setSize(sf::Vector2f(healthBarWidth, healthBarHeight));
    healthOutline->setOutlineColor(sf::Color::White);
    healthOutline->setOutlineThickness(healthBarThickness);
    healthOutline->setFillColor(sf::Color::Black);
    healthOutline->setPosition(column1Offset, row1Offset);
    interface.push_back(healthOutline);

    float healthBarAmount;
    if(p.getHealth() > 0) { // In case of negative health
        float healthRatio = p.getHealth() / 100.0f;
        healthBarAmount = healthBarWidth * healthRatio;
    } else {
        healthBarAmount = 0;
    }
    sf::RectangleShape * healthBar = new sf::RectangleShape();
    healthBar->setSize(sf::Vector2f(healthBarAmount, healthBarHeight));
    healthBar->setFillColor(sf::Color::Red);
    healthBar->setPosition(column1Offset, row1Offset);
    interface.push_back(healthBar);

    // Weapons (column 1, row 2)

    // Gun

    sf::Text * xText = new sf::Text();
    xText->setString("x: supah lazar");
    xText->setCharacterSize(50);
    xText->setColor(sf::Color::Yellow);
    xText->setPosition(column1Offset, row2Offset);
    interface.push_back(xText);


    // Score (column 2, row 2)

    sf::Text * scoreText = new sf::Text();
    if(score > 300 || last_score == 0){
        scoreText->setString(processScore(score) + "\n");
        scoreText->setCharacterSize(90);
    } else {
        scoreText->setString("STOP DYING\n");
        scoreText->setCharacterSize(63);
    }

    scoreText->setColor(sf::Color::Green);
    scoreText->setPosition(column2Offset, row2Offset);
    interface.push_back(scoreText);

    if(last_score > 0){
        sf::Text * lastScoreText = new sf::Text();
        lastScoreText->setString("Last Score: " + processScore(last_score) + "\n");
        lastScoreText->setCharacterSize(30);
        lastScoreText->setColor(sf::Color::Green);
        lastScoreText->setPosition(column2Offset + 10, row2Offset + 90);
        interface.push_back(lastScoreText);
    }
}

void updateGameClocks() {
    if(time_since_fire < SHOOTING_OFFSET)
        time_since_fire++;

    float current_time = fps_clock.restart().asSeconds();
    float fps = 1.f / (current_time - last_time);
    last_time = current_time;

    //printf("fps: %f\n", fps);
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

    last_time = 0;
    last_score = 0;
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
    last_score = score;
    score = 1;
    time_since_fire = SHOOTING_OFFSET;
    
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
            updateScore();
            updateInterface();
            updateGameClocks();

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

            for(std::vector<sf::Drawable*>::iterator iter = interface.begin(); iter != interface.end(); ++iter) {
                sf::Drawable *d = *iter;
                window.draw(*d);
            }

            window.display();
        }

        setupEntities();
        game_running = true;
    }
    return 0;
}
