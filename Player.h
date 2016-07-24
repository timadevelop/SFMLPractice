//
// Created by vtimofeev on 18/06/16.
//

#ifndef GAME_PLAYER_H
#define GAME_PLAYER_H

#include "entity.h"
#include "projectile.h"
#include "textDisplay.h"
#include "Organism.h"
#include "Block.h"


class Player : public entity, public Organism
{
private:
    Projectile projectile;
    std::vector<Block> track;
    float normalSpeed = 2;
    int rotationFactor = 0, rotationAngle = 5;
public:

    sf::CircleShape mainCircle, secondCircle, thirdCircle;
    sf::RectangleShape target;
    Player();
    ~Player();
    void update();
    void updateMovement(); // update Player if some Key from [Up, Down, Right, Left] is pressed
    textDisplay takeDamage(textDisplay&, int); // returns damage message with Player position
    Projectile fire(); // returns new projectile
    Projectile fire(sf::RectangleShape);
    Projectile getProjectile() const;
	void setProjectile(Projectile);
    unsigned int destroyedEnemies = 0;
    void setTarget(sf::RectangleShape);
    void draw(sf::RenderWindow* window);
};


#endif //GAME_PLAYER_H