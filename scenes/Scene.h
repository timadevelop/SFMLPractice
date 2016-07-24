//
// Created by vtimofeev on 01/07/16.
//

#ifndef GAME_GAMESCREEN_H
#define GAME_GAMESCREEN_H


#include <SFML/Graphics/RenderWindow.hpp>

class Scene {
public:
    int result = 0;
    virtual int Run(sf::RenderWindow& App) = 0;
    virtual int getResult() = 0;
};


#endif //GAME_GAMESCREEN_H
