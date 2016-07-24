//
// Created by vtimofeev on 05/07/16.
//

#ifndef GAME_THEENDSCENE_H
#define GAME_THEENDSCENE_H

#include "Scene.h"
#include "MenuScene.h"
#include "GameScene.h"

class TheEndScene : public Scene{
public:
    TheEndScene();
    int Run(sf::RenderWindow&);
    int getResult();
};


#endif //GAME_THEENDSCENE_H
