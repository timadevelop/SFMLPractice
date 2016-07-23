    //
// Created by vtimofeev on 01/07/16.
//

#ifndef GAME_SCREEN_1_H
#define GAME_SCREEN_1_H


#include <SFML/Graphics.hpp>
#include <iostream>
#include "Scene.h"
#include "../textDisplay.h"
#include "../Wall.h"
#include "../Player.h"
#include "../Enemy.h"

using namespace std;

class GameScene : public Scene {
private:

    // Variables
    sf::Clock fireclock;
    sf::Clock damageClock;
    sf::Clock clock3;
    int counter = 0;
    int counter2 = 0;
    int counter3 = 0;

    sf::View view;


    sf::Texture texture;
    sf::Sprite background;

    sf::Font font;
    sf::Text gameInfo = sf::Text("Welcome", font, 30);

    sf::Texture enemyTexture;

    textDisplay hint; // hint proto
    vector<textDisplay> hints;
    vector<textDisplay>::const_iterator hintIter;

    Wall wall; // wall proto
    vector<Wall> room;
    vector<Wall>::const_iterator wallIterator;

    Enemy enemy;
    vector<Enemy> enemies;
    vector<Enemy>::const_iterator iterEnemies;

    // Projectile Vector Array
    vector<Projectile>::const_iterator iter;
    vector<Projectile> projectiles;
    // Text Vector Array
    textDisplay msg;     // msg prototype
    vector<textDisplay>::const_iterator textIterator;
    vector<textDisplay> msgs;

    Player player;
    // deletes enemies with destroy == true from enemies vector
    template <class entityType>
    bool destroyEntities(vector<entityType>& entities);

    // adds new hint in bottom right corner and deletes excess hint
    void addHint(vector<textDisplay>& hints, textDisplay& hint, std::string txt, int);


public:
    GameScene(sf::RenderWindow &); // game loop
    int Run(sf::RenderWindow &);
    int getResult();
};

#endif //GAME_SCREEN_1_H
