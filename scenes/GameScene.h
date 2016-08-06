    //
// Created by vtimofeev on 01/07/16.
//

#ifndef GAME_SCREEN_1_H
#define GAME_SCREEN_1_H


#include <SFML/Graphics.hpp>
#include <iostream>
#include "Scene.h"
#include "../textDisplay.h"
#include "../Block.h"
#include "../Player.h"
#include "../Enemy.h"

using namespace std;

class GameScene : public Scene {
private:

    // Variables
    sf::Clock fireclock;
    sf::Clock damageClock;
    sf::Clock enemyCollisionClock;
	int enemiesCount = 10;
	int maxtargets = 3;
	int level = 1;
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
    vector<textDisplay>::iterator hintIter;

    Block block; // block proto
    vector<Block> room;
    vector<Block>::iterator blockIterator;

    Enemy enemy;
    vector<Enemy> enemies;
    vector<Enemy>::iterator iterEnemies;

    // Projectile Vector Array
    vector<Projectile>::iterator iterProjectiles;
    vector<Projectile> projectiles;
    // Text Vector Array
    textDisplay msg;     // msg prototype
    vector<textDisplay>::iterator textIterator;
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
