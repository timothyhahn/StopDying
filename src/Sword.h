#ifndef SWORD_H
#define SWORD_H
#include "Entity.h"
#include <stdlib.h>

class Sword : public Entity {
    private:
        bool _swung;
        float _angle; // from 0 to 90 degrees
        float _startAngle;
        float _finalAngle;
    public:

        /**
         * Default constructor. Will initialize default Enemy settings
         */
        Sword();

        bool isSwung();
        void setSwung(bool swung);
        float getAngle();
        void setStartAngle(float startAngle);
        
        void swing();
       
        /**
         * Sword's `createShape` that overrides Bullet's virtual createShape
         */
        void createShape();
        bool swordColliding(Entity e);
};

#endif
