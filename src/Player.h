#ifndef PLAYER_H
#define PLAYER_H
#include "Entity.h"

class Player : public Entity {
    public:
        
        /**
         * Default constructor
         * Sets up default Player settings
         */
        Player();

        /**
         * Player's `createShape`. Overrides Entity's `createShape`
         */
        void createShape();

};
#endif
