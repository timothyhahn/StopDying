#ifndef PLAYER_H
#define PLAYER_H
#include "Entity.h"
#include "Bullet.h"
#include "Sword.h"
#include <vector>
class Player : public Entity {
    private:
        std::vector<Bullet*> _bullets;
        Sword *_sword;
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
        Sword * getSword();
        
        /**
         * Player's `createShape`. Overrides Entity's `createShape`
         */
        void createShape();



        void shoot();
        void swing();

};
#endif
