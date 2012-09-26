#ifndef GAME_H
#define GAME_H

#include "Entity.h"
#include <stdio.h>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include <string>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

static sf::RenderWindow window;

class Game {
    public:
        int initialize();
        int start();

};

#endif
