#ifndef BULLET_H
#define BULLET_H
#include "Entity.h"
#include "Player.h"
#include <stdlib.h>

class Bullet : public Entity {
    public:

        /**
         * Default constructor. Will initialize default Enemy settings
         */
        Bullet();

        /**
         * Tells the enemy to find the player and try to catch them
         * @param p The player that the enemy wants to satlk
         */
        void fire(Direction d);
       
        /**
         * Bulllet's `createShape` that overrides Bullet's virtual createShape
         */
        void createShape();
};

#endif
