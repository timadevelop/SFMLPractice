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
    float movementSpeed = 10;
    int counterLifeTime = 0 , lifeTime = 200;
    float rechargeSpeed = 70;
    std::string name = "Shotgun";
public:
    Projectile();
    void update();
    bool destroy = false;
    int getAttackDamage() const;
    void setAttackDamage(int);
    float getRechargeSpeed() const;
    std::string getName() const;
    void setName(std::string);
};


#endif //GAME_PROJECTILE_H
