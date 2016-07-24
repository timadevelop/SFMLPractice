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

    int changeSpritePerFrames = 3; // change walking sprite every {changeSpriteFrames}
    int changeSpriteCounter = 0;
    float movementSpeed = 2;
public:
    bool destroy = false;
    virtual textDisplay takeDamage(textDisplay& msg, int damage, sf::Vector2f rectPosition);
    void changeWalkingSprite(); // changes sprite per changeSpritePerFrames

    int getHp() const;
    void setHp(int);
    int getAttackDamage() const;
    void setAttackDamage(int);
    float getMovementSpeed() const;
};


#endif //GAME_ORGANISM_H
