//
// Created by vtimofeev on 19/06/16.
//

#ifndef GAME_ENEMY_H
#define GAME_ENEMY_H


#include "entity.h"
#include "randoms.h"
#include "textDisplay.h"

class Enemy : public entity
{
private:
    int attackDamage = 2;
    int counter = 0;
    int hp = 2;
    int walkingCounter = 0;
    int movementLength = 100;
    float movementSpeed = .5;
public:
    bool destroy = false;
    Enemy();
    void update();
    void updateMovement();
    textDisplay takeDamage(textDisplay&, int);
    int getHp() const;
    void setHp(int);
    int getAttackDamage() const;
    float getMovementSpeed() const;
    void setAttackDamage(int);
};


#endif //GAME_ENEMY_H
