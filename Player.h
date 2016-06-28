//
// Created by vtimofeev on 18/06/16.
//

#ifndef GAME_PLAYER_H
#define GAME_PLAYER_H

#include "entity.h"
#include "projectile.h"
#include "textDisplay.h"


class Player : public entity
{
private:
    int walkingCounter = 0;
    int hp = 20;
    Projectile projectile;
    // value of current speed of Player/
    float movementSpeed = 2;
    float normalSpeed = 2;
public:
    int attackDamage = 5;
    Player();
    void update();
    void updateMovement();
    void backAway(int);
    // interface
    int getHp() const;
    void setHp(int);
    Projectile getProjectile() const;
    Projectile fire(); // returns new projectile
    textDisplay takeDamage(textDisplay&, int);
    float getMovementSpeed() const;
};


#endif //GAME_PLAYER_H