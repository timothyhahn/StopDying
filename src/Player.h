#ifndef PLAYER_H
#define PLAYER_H
#include "Entity.h"
#include "Bullet.h"
#include <vector>
class Player : public Entity {
    private:
        std::vector<Bullet*> _bullets;
    public:
        /**
         * Default constructor
         * Sets up default Player settings
         */
        Player();

        /**
         * Accessor and mutators
         */
        std::vector<Bullet*> getBullets();
        void setBullets(std::vector<Bullet*>);
        
        /**
         * Player's `createShape`. Overrides Entity's `createShape`
         */
        void createShape();

        void shoot();

};
#endif
