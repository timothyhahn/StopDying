#ifndef ENEMY_H
#define ENEMY_H
#include "Entity.h"
#include "Player.h"
#include <stdlib.h>

class Enemy : public Entity {
    public:

        /**
         * Default constructor. Will initialize default Enemy settings
         */
        Enemy();

        /**
         * Tells the enemy to find the player and try to catch them
         * @param p The player that the enemy wants to satlk
         */
        void stalkPlayer(Player p);
       
        /**
         * Enemy's `createShape` that overrides Entity's virtual createShape
         */
        void createShape();
};

#endif
