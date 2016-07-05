//
// Created by vtimofeev on 18/06/16.
//

#ifndef GAME_PLAYER_H
#define GAME_PLAYER_H

#include "entity.h"
#include "projectile.h"
#include "textDisplay.h"
#include "Organism.h"


class Player : public entity, public Organism
{
private:
    Projectile projectile;
    float normalSpeed = 2;
public:
    Player();
    void update();
    void updateMovement(); // update Player if some Key from [Up, Down, Right, Left] is pressed
    textDisplay takeDamage(textDisplay&, int); // returns damage message with Player position
    Projectile fire(); // returns new projectile
    Projectile getProjectile() const;

    unsigned int destroyedEnemies = 0;
};


#endif //GAME_PLAYER_H