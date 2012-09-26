#ifndef ENEMY_H
#define ENEMY_H
#include "Entity.h"
#include "Player.h"
#include <stdlib.h>

class Enemy : public Entity {
    public:
        Enemy();
        void stalkPlayer(Player p);
        void createShape();
};

#endif
