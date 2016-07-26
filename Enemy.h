//
// Created by vtimofeev on 19/06/16.
//

#ifndef GAME_ENEMY_H
#define GAME_ENEMY_H


#include "entity.h"
#include "helpers/randoms.h"
#include "textDisplay.h"
#include "Organism.h"

class Enemy : public entity, public Organism
{
private:
    int counter = 0; // for ai
    int movementLength = 100;
	sf::RectangleShape target;
public:
    Enemy();
    void update();
	void setTarget(sf::RectangleShape);

    // sets random direction and moves enemy
    void updateMovement();
};


#endif //GAME_ENEMY_H
