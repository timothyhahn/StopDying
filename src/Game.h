#ifndef GAME_H
#define GAME_H

#include "Entity.h"
#include "Player.h"
#include "Enemy.h"
#include "Bullet.h"
#include <stdio.h>
#include <stdlib.h>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include <string>
#include <sstream>
#include <cmath>
#include <time.h>
#include <vector>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 800
#define GAME_HEIGHT 600

static const int GAME_WIDTH = SCREEN_WIDTH;
static const int INTERFACE_WIDTH = SCREEN_WIDTH;
static const int INTERFACE_HEIGHT = SCREEN_HEIGHT - GAME_HEIGHT;

static const int SHOOTING_OFFSET = 5;

static sf::RenderWindow window;
static Player p;
static std::vector<Bullet *> bullets;
static std::vector<Enemy *> enemies; // Non Player Entities
static std::vector<sf::Drawable*> interface;
static bool game_over;
static bool game_running;
static float spawn_rate;
static unsigned long int score;
static int time_since_fire;
static float last_time;
static float current_time;
static sf::Clock fps_clock;

class Game {

    public:
        int initialize();
        int setupEntities();
        int start();
};

#endif
