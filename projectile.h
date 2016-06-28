//
// Created by vtimofeev on 19/06/16.
//

#ifndef GAME_PROJECTILE_H
#define GAME_PROJECTILE_H

#include "string"
#include "entity.h"

class Projectile : public entity
{
private:
    int attackDamage = 1;
    int movementSpeed = 10;
    float rechargeSpeed = 70;
    std::string name = "Shotgun";
public:
    int counterLifeTime = 0 , lifeTime = 200;
    Projectile();
    void update();
    bool destroy = false;
    int getAttackDamage() const;
    void setAttackDamage(int);
    float getRechargeSpeed() const;
    std::string getName() const;
};


#endif //GAME_PROJECTILE_H
