#ifndef GAME_H
#define GAME_H

#include "Entity.h"
#include "Player.h"
#include "Enemy.h"
#include <stdio.h>
#include <stdlib.h>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include <string>
#include <cmath>
#include <time.h>
#include <vector>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

static sf::RenderWindow window;
static Player p;
static std::vector<Enemy *> enemies; // None Player Entities
static bool game_over;
static bool game_running;
class Game {

    public:
        int initialize();
        int setupEntities();
        int start();
};

#endif
