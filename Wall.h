//
// Created by vtimofeev on 27/06/16.
//

#ifndef GAME_BRICK_H
#define GAME_BRICK_H

#include "vector"
#include "entity.h"

class Wall : public entity
{
private:
    float width = 50, height = 50;
public:
    Wall();
    Wall(float, float);
};


#endif //GAME_BRICK_H
