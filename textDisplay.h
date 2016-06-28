//
// Created by vtimofeev on 19/06/16.
//

#ifndef GAME_TEXTDISPLAY_H
#define GAME_TEXTDISPLAY_H

#include <string>

#include <SFML/Graphics.hpp>
#include "entity.h"


class textDisplay : public entity
{
private:
    float movementSpeed = 1;
    sf::Vector2f moveVector = sf::Vector2f(-0.3 ,-movementSpeed);
public:
    bool destroy = false;
    int lifeTime = 100;
    int counter = 0;
    std::string str = "Default";
    textDisplay();
    void update();
    void setMoveVector(sf::Vector2f);
};


#endif //GAME_TEXTDISPLAY_H
