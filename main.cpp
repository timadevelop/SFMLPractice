#include <iostream>
#include <SFML/Graphics.hpp>

using namespace std;

#include "randoms.h"

#include "Player.h"
#include "projectile.h"
#include "Enemy.h"
#include "textDisplay.h"
#include "Wall.h"

template<class entityType>
bool destroyEntities(vector<entityType>& entities); // deletes enemies with destroy == true from enemies vector

void addHint(vector<textDisplay>& hints, textDisplay& hint, std::string txt, int);


int main()
{
    // Variables
    sf::Clock fireclock;
    sf::Clock damageClock;
    sf::Clock clock3;
    int counter = 0;
    int counter2 = 0;
    int counter3 = 0;
    const int X_MAX = 1800;
    const int Y_MAX = 1080;
    sf::RenderWindow window(sf::VideoMode(X_MAX, Y_MAX), "SFML Application");
    window.setFramerateLimit(60);

    // Background
    sf::Texture texture;
    if (!texture.loadFromFile("src/back.jpg"))
        return EXIT_FAILURE;
    texture.setRepeated(true);
    sf::Sprite background(texture);
    background.setTextureRect(sf::IntRect(0,0, window.getSize().x, window.getSize().y));

    // Text
    sf::Font font;
    if(!font.loadFromFile("src/fonts/invation2000.ttf"))
        return EXIT_FAILURE;

    sf::Text gameInfo("Welcome", font, 30);
    gameInfo.setColor(sf::Color::White);


    // Textures
    sf::Texture heroTexture ;
    if(!heroTexture.loadFromFile("src/mario.png"))
        return EXIT_FAILURE;

    sf::Texture enemyTexture;
    if(!enemyTexture.loadFromFile("src/enemy.png"))
        return EXIT_FAILURE;

    // ****************************
    //          Hints
    // ****************************

    vector<textDisplay> hints;
    vector<textDisplay>::const_iterator hintIter;
    textDisplay hint;
    hint.setMoveVector(sf::Vector2f(0, -1));//hint.text.getCharacterSize()));
    hint.text.setFont(font);
    hint.text.setCharacterSize(15);
    addHint(hints, hint, "LShift - boost", X_MAX);
    addHint(hints, hint, "W - wall painting mode", X_MAX);
    // ****************************
    //          Entities
    // ****************************


    vector<Wall>::const_iterator roomIterator;
    vector<Wall> room;
    // Window borders
    Wall wall(window.getSize().x, 50); // upper
    room.push_back(wall);
    wall.rect.setPosition(0, window.getSize().y);
    room.push_back(wall);
    wall = Wall(50, window.getSize().y);
    room.push_back(wall);
    wall.rect.setPosition(window.getSize().x, 0);
    room.push_back(wall);

    Player Player1;
    Player1.sprite.setTexture(heroTexture);


    vector<Enemy>::const_iterator iterEnemies;
    vector<Enemy> enemies;
    Enemy enemy;
    enemy.sprite.setTexture(enemyTexture);
    enemies.push_back(enemy);

    // Projectile Vector Array
    vector<Projectile>::const_iterator iter;
    vector<Projectile> projectiles;

    // Text Vector Array
    vector<textDisplay>::const_iterator textIterator;
    vector<textDisplay> msgs;

    // msg prototype
    textDisplay msg;
    msg.text.setFont(font);

    while (window.isOpen())
    {
        sf::Event event;

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
                window.close();
        }

        window.clear();

        sf::Time elapsedFireClock = fireclock.getElapsedTime();
        sf::Time elapsedDamageClock = damageClock.getElapsedTime();
        sf::Time elapsed3 = clock3.getElapsedTime();

        // Fire missle (space bar)

        if(elapsedFireClock.asSeconds() >= 10/Player1.getProjectile().getRechargeSpeed()) { // for @small@ projectiles
            fireclock.restart();
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
                if (Player1.direction != Direction::None)
                    projectiles.push_back(Player1.fire());
            }
        }


        // ****************************
        //          Collisions
        // ****************************

        // Entity Collides with wall

        counter = 0;
        for (roomIterator = room.begin(); roomIterator != room.end(); roomIterator++, counter++) {
            if(Player1.intersects(room[counter]))
            {
                Player1.backAway(Player1.getMovementSpeed());
            }
            counter2 = 0;
            for (iterEnemies = enemies.begin(); iterEnemies != enemies.end(); iterEnemies++, counter2++) {
                if (room[counter].intersects(enemies[counter2])) {
                    enemies[counter2].backAway(enemies[counter2].getMovementSpeed()+1);
                }
            }
        }

        // Projectile Collides with enemy

        counter = 0;
        for (iter = projectiles.begin(); iter != projectiles.end(); iter++, counter++) {
            counter2 = 0;
            for (iterEnemies = enemies.begin(); iterEnemies != enemies.end(); iterEnemies++, counter2++) {
                if (projectiles[counter].intersects(enemies[counter2])) {
                    enemies[counter2].takeDamage(msg, projectiles[counter].getAttackDamage());
                    projectiles[counter].destroy = true;
                    msgs.push_back(msg);
                }
            }
        }

        // Enemy collides with player (player takes damage)
        counter = 0;
        for (iterEnemies = enemies.begin(); iterEnemies != enemies.end(); iterEnemies++, counter++) {
            if (enemies[counter].intersects(Player1)) {
                Player1.takeDamage(msg, enemies[counter].getAttackDamage());
                msgs.push_back(msg);
            }
        }

        // ****************************
        //          Destroing
        // ****************************

        // Destroy player
        if(Player1.getHp() <= 0 && Player1.rect.getScale() != sf::Vector2f(0,0))
        {
            hint.text.setColor(sf::Color::Red);
            addHint(hints, hint, "You are destroyed", X_MAX);
            Player1.rect.scale(0,0);
            Player1.sprite.scale(0,0);
        }
        destroyEntities<Projectile>(projectiles);
        destroyEntities<textDisplay>(msgs);
        if( destroyEntities<Enemy>(enemies) )
        {
            addHint(hints, hint, "Player destroyed enemy", X_MAX);
        }
        // ****************************
        //          Hotkeys
        // ****************************

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::A) && enemies.size() < 20)
        {
            enemy.rect.setPosition(generateRandom(window.getSize().x), generateRandom(window.getSize().y));
            enemies.push_back(enemy);
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        {
            wall.rect.setSize(sf::Vector2f(10,10));
            wall.rect.setPosition(Player1.rect.getPosition().x-10, Player1.rect.getPosition().y-10);
            room.push_back(wall);
        }

        // ****************************
        //          Drawing
        // ****************************

        //window.draw(background);
        window.draw(wall.rect);

        // Drawing walls
        counter = 0;
        for (roomIterator = room.begin(); roomIterator != room.end(); roomIterator++, counter++) {
            window.draw(room[counter].rect);
        }

        // Drawing projectiles
        counter = 0;
        for (iter = projectiles.begin(); iter != projectiles.end(); iter++, counter++) {
            projectiles[counter].update();
            window.draw(projectiles[counter].rect);
        }

        // Drawing enemies
        counter = 0;
        for (iterEnemies = enemies.begin(); iterEnemies != enemies.end(); iterEnemies++, counter++) {
            enemies[counter].update();
            window.draw(enemies[counter].sprite);
        }

        Player1.update();
        window.draw(Player1.sprite);

        // Update & draw information

        gameInfo.setString("Hero HP: " + to_string(Player1.getHp()) + " | Enemies: " + to_string(enemies.size()) + " | Weapon: " + Player1.getProjectile().getName());
        window.draw(gameInfo);


        // Drawing hints
        counter = 0;
        for (hintIter = hints.begin(); hintIter != hints.end(); hintIter++) {
            window.draw(hints[counter].text);
            counter++;
        }


        // ****************************
        //          Damage showing
        // ****************************
        counter = 0;
        for (textIterator = msgs.begin(); textIterator != msgs.end(); textIterator++) {
            msgs[counter].update();
            window.draw(msgs[counter].text);
            counter++;
        }

        window.display();
    }
}


template<class entityType>
bool destroyEntities(vector<entityType>& entities)
{
    bool destroyed = false;
    typename vector<entityType>::const_iterator entityIterator;
    int c = 0;
    for (entityIterator = entities.begin(); entityIterator != entities.end(); entityIterator++) {
        if(entities[c].destroy)
        {
            entities.erase(entityIterator);
            destroyed = true;
            break;
        }
        c++;
    }
    return destroyed;
}

void addHint(vector<textDisplay>& hints, textDisplay& hint, std::string txt, int X_MAX)
{
    if(hints.size() > 10) {
        hints.erase(hints.begin());
    }
    int counter = 0;
    vector<textDisplay>::const_iterator hintIter;
    for (hintIter = hints.begin(); hintIter != hints.end(); hintIter++) {
        hints[counter].text.move(0, -15);
        counter++;
    }

    hint.text.setString(txt);
    hint.text.setPosition(X_MAX - hint.text.getGlobalBounds().width - 50, 1000);
    hints.push_back(hint);
}