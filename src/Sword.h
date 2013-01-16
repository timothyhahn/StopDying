#ifndef SWORD_H
#define SWORD_H
#include "Entity.h"
#include <stdlib.h>

class Sword : public Entity {
    private:
        bool _swung;
        float _angle; // from 0 to 90 degrees
    public:

        /**
         * Default constructor. Will initialize default Enemy settings
         */
        Sword();

        bool isSwung();
        void setSwung(bool swung);
        float getAngle();
        
        /**
         * Tells the enemy to find the player and try to catch them
         * @param p The player that the enemy wants to satlk
         */
        void swing();
       
        /**
         * Sword's `createShape` that overrides Bullet's virtual createShape
         */
        void createShape();
};

#endif
