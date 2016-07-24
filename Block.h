//
// Created by vtimofeev on 27/06/16.
//

#ifndef GAME_BRICK_H
#define GAME_BRICK_H

#include "vector"
#include "entity.h"

class Block : public entity
{
private:
    float width = 50, height = 50;
public:
    sf::CircleShape circle;
    sf::Transform transform;
    bool isBarrier = true;
    Block();
    Block(float, float);
};


#endif //GAME_BRICK_H
