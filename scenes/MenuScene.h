//
// Created by vtimofeev on 01/07/16.
//

#ifndef GAME_SCREEN_0_H
#define GAME_SCREEN_0_H
#include <iostream>
#include "scenes/Scene.h"
#include <SFML/Graphics.hpp>

class MenuScene : public Scene
{
private:
    bool playing;
public:
    MenuScene();
    virtual int Run(sf::RenderWindow &App);
    void reset();
    int getResult();
};

#endif //GAME_SCREEN_0_H
