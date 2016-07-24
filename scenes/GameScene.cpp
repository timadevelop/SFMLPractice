//
// Created by vtimofeev on 01/07/16.
//

#include "GameScene.h"
#include "../helpers/randoms.h"

int GameScene:: getResult()
{
    return player.destroyedEnemies*enemy.getHp()*player.getHp();
}

GameScene::GameScene(sf::RenderWindow &window) {
    // View
    view.setSize(window.getSize().x/2, window.getSize().y/2);
    view.setCenter(player.rect.getPosition()); // default center
    window.setView(view);
    // Background
    if (!texture.loadFromFile("src/back.jpg"))
        std::cerr << "This .jpg file is not found";
    texture.setRepeated(true);
    background.setTexture(texture);
    background.setTextureRect(sf::IntRect(0,0, window.getSize().x, window.getSize().y));


    // Text
    if(!font.loadFromFile("src/fonts/invation2000.ttf"))
        std::cerr << "This .ttf file is not found";
    sf::Text gameInfo("Welcome", font, 30);
    gameInfo.setColor(sf::Color::White);

    if(!enemyTexture.loadFromFile("src/enemy.png"))
        std::cerr << "This .png file for texture is not found";

    // ****************************
    //          Hints
    // ****************************
    hint.setMoveVector(sf::Vector2f(0, -1));//hint.text.getCharacterSize()));
    hint.text.setFont(font);
    hint.text.setCharacterSize(15);
    addHint(hints, hint, "LShift - boost", window.getSize().x);
    addHint(hints, hint, "Left mouse - fire", window.getSize().x);
    addHint(hints, hint, "Right mouse / arrows - walking", window.getSize().x);

    // ****************************
    //          Entities
    // ****************************

    // Map borders
    block = Block(window.getSize().x, 50); // upper
    room.push_back(block);
    block.rect.setPosition(0, window.getSize().y);
    room.push_back(block);
    block = Block(50, window.getSize().y);
    room.push_back(block);
    block.rect.setPosition(window.getSize().x, 0);
    room.push_back(block);
    block.rect.setFillColor(sf::Color::White);
    // Player

    player.mainCircle.setPosition(window.getSize().x/2, window.getSize().y/2);
    player.rect.setPosition(window.getSize().x/2, window.getSize().y/2);
    // Enemies
    enemy.sprite.setTexture(enemyTexture);
	for (int i = 0; i <= 10; ++i) {
        enemy.rect.setPosition(generateRandom(window.getSize().x - 100), generateRandom(window.getSize().y - 100));
        enemies.push_back(enemy);
    }
    msg.text.setFont(font);
    msg.text.setCharacterSize(13);
}


int GameScene::Run(sf::RenderWindow &window) {

    window.setTitle("Game");
    window.setView(view);

	bool boss = false;
	while (window.isOpen()) {
        sf::Event event;

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                return -1;
            }
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                return 0;
            }
            if(event.type == sf::Event::LostFocus){
                return 0;
            }
        }

        window.clear();

        sf::Time elapsedFireClock = fireclock.getElapsedTime();
        sf::Time elapsedDamageClock = damageClock.getElapsedTime();
        sf::Time elapsed3 = clock3.getElapsedTime();

        // Fire (space bar)

        if (elapsedFireClock.asSeconds() >= 10 / player.getProjectile().getRechargeSpeed()) { // for @small@ projectiles
            fireclock.restart();
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) &&
                player.directionVector != sf::Vector2f(0, 0) )
            {
                projectiles.push_back(player.fire());
            } else if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                sf::Vector2i localPosition = sf::Mouse::getPosition(window);
                sf::Vector2f worldPosition = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                sf::RectangleShape target;
                target.setPosition(worldPosition);
                target.setSize(sf::Vector2f(10,10));
                target.setFillColor(sf::Color::White);
                projectiles.push_back(player.fire(target));
            }
        }

        // motion
        if (sf::Mouse::isButtonPressed(sf::Mouse::Right) &&
            !player.rect.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))))
        {
            sf::Vector2i localPosition = sf::Mouse::getPosition(window);
            sf::Vector2f worldPosition = window.mapPixelToCoords(sf::Mouse::getPosition(window));
            sf::RectangleShape target;
            target.setPosition(worldPosition);
            target.setSize(sf::Vector2f(10,10));
            target.setFillColor(sf::Color::White);
            player.setTarget(target);
        }

        // ****************************
        //          Collisions
        // ****************************

        // Entity Collides with block

        counter = 0;
        for (blockIterator = room.begin(); blockIterator != room.end(); blockIterator++, counter++) {
            if(!room[counter].isBarrier)
                continue;
            if (player.intersects(room[counter])) {
                player.backAway(player.getMovementSpeed());
            }
            counter2 = 0;
            for (iterEnemies = enemies.begin(); iterEnemies != enemies.end(); iterEnemies++, counter2++) {
                if (room[counter].intersects(enemies[counter2])) {
                    enemies[counter2].backAway(enemies[counter2].getMovementSpeed());
                }
            }
        }

        // Projectile Collides with enemy

        counter = 0;
        for (iter = projectiles.begin(); iter != projectiles.end(); iter++, counter++) {
            counter2 = 0;
            for (iterEnemies = enemies.begin(); iterEnemies != enemies.end(); iterEnemies++, counter2++) {
                if (projectiles[counter].intersects(enemies[counter2])) {
                    enemies[counter2].takeDamage(msg, projectiles[counter].getAttackDamage(),
                                                 enemies[counter2].rect.getPosition());
                    projectiles[counter].destroy = true;
                    if (enemies[counter2].destroy)
                        addHint(hints, hint, "Player destroyed enemy", window.getSize().x);
                    msgs.push_back(msg); // damage msg
                }
            }
        }

        // Enemy collides with player (player takes damage)
        counter = 0;
        for (iterEnemies = enemies.begin(); iterEnemies != enemies.end(); iterEnemies++, counter++) {
            if (enemies[counter].intersects(player)) {
                player.takeDamage(msg, enemies[counter].getAttackDamage());
                msgs.push_back(msg);
            }
        }

        // ****************************
        //          Destroying
        // ****************************

        // The end
        if (player.getHp() <= 0 && player.rect.getScale() != sf::Vector2f(0, 0))
            break; // the end of game

		if (enemies.size() == 0)
		{
			if (boss)
				break;
			Enemy chicken = enemy;
			chicken.setHp(40);
			chicken.setMovementSpeed(chicken.getMovementSpeed() * 2);
			chicken.sprite.setScale(1.5, 1.5);
			chicken.rect.setScale(1.5, 1.5);
			chicken.setAttackDamage(3);
			chicken.rect.setPosition(generateRandom(window.getSize().x - 100), generateRandom(window.getSize().y - 100));
			enemies.push_back(chicken);
			Projectile pr;
			pr.setAttackDamage(2);
			pr.setRechargeSpeed(pr.getRechargeSpeed() * 2);
			pr.setName("QuickFire");
			player.setProjectile(pr);
			boss = true;
			addHint(hints, hint, "Find main CHICKEN!", window.getSize().x);
		}

        destroyEntities<Projectile>(projectiles);

        if(destroyEntities<Enemy>(enemies))
            player.destroyedEnemies++;

        destroyEntities<textDisplay>(msgs);

        // ****************************
        //          Hotkeys
        // ****************************

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::E) && enemies.size() < 70 && !boss) {
            enemy.rect.setPosition(generateRandom(window.getSize().x - 100), generateRandom(window.getSize().y - 100));
            enemies.push_back(enemy);
        }

        // ****************************
        //          Drawing
        // ****************************
        window.draw(background);

        // Drawing Player blocks
        counter = 0;
        for (blockIterator = room.begin(); blockIterator != room.end(); blockIterator++, counter++) {
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

        // Drawing damage
        counter = 0;
        for (textIterator = msgs.begin(); textIterator != msgs.end(); textIterator++) {
            msgs[counter].update();
            window.draw(msgs[counter].text);
            counter++;
        }
        player.update();

        // drawing player
        player.draw(&window);

        // *************************
        // Update & draw information
        // drawing blocks with
        // standart view
        // *************************

        // setting view for drawing main info
        window.setView(window.getDefaultView());

        gameInfo.setString(
                "Hero HP: " + to_string(player.getHp()) + " | Enemies: " + to_string(enemies.size()) + " | Weapon: " +
                player.getProjectile().getName());
        window.draw(gameInfo);


        // Drawing hints
        counter = 0;
        for (hintIter = hints.begin(); hintIter != hints.end(); hintIter++) {
            window.draw(hints[counter].text);
            counter++;
        }
        view.setCenter(player.rect.getPosition());
        window.setView(view);
        window.display();
    }


    return 2;
}


template<class entityType>
bool GameScene::destroyEntities(vector<entityType>& entities)
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

void GameScene::addHint(vector<textDisplay>& hints, textDisplay& hint, std::string txt, int X_MAX)
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
