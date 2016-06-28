//
// Created by vtimofeev on 28/06/16.
//

#ifndef GAME_ORGANISM_H
#define GAME_ORGANISM_H


#include "textDisplay.h"

class Organism {
protected:
    int hp = 2,
        walkingCounter = 0,
        attackDamage = 0;
    float movementSpeed = 2;
public:
    bool destroy = false;
    virtual textDisplay takeDamage(textDisplay& msg, int damage, sf::Vector2f rectPosition);

    int getHp() const;
    void setHp(int);
    int getAttackDamage() const;
    void setAttackDamage(int);
    float getMovementSpeed() const;
};


#endif //GAME_ORGANISM_H
