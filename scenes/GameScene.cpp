//
// Created by vtimofeev on 01/07/16.
//

#include "GameScene.h"
#include "../helpers/randoms.h"


std::vector<Block> generateRoom(sf::RenderWindow* window, std::vector<Block>::iterator blocksBegin, std::vector<Block>::iterator blocksEnd);

int GameScene:: getResult()
{
    return player.destroyedEnemies*enemy.getHp()*(player.getHp() > 1 ? player.getHp() : 1);
}

GameScene::GameScene(sf::RenderWindow &window) {
    // View
    view.setSize(static_cast<float>(window.getSize().x/2), static_cast<float>(window.getSize().y/2));
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
	enemyTexture.setSmooth(true);
    // ****************************
    //          Hints
    // ****************************
    hint.setMoveVector(sf::Vector2f(0, -1));
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
	//player.setMovementSpeed(enemy.getMovementSpeed()*1.4f);
    player.rect.setPosition(window.getSize().x/2, window.getSize().y/2);
    // Enemies
    enemy.sprite.setTexture(enemyTexture);
	for (int i = 0; i <= enemiesCount; ++i) {
		enemy.setMovementSpeed(generateRandomFloat(.5f, 1.0f));
        enemy.rect.setPosition(generateRandomFloat(enemy.rect.getSize().x + 10 ,window.getSize().x - 100), generateRandomFloat(enemy.rect.getSize().y + 10, window.getSize().y - 100));
        enemies.push_back(enemy);
    }
    msg.text.setFont(font);
    msg.text.setCharacterSize(13);

}


int GameScene::Run(sf::RenderWindow &window) {

    window.setTitle("Game");
    window.setView(view);
	int mouseDelta = 0;
	int rooms = 0;
	const int maxRooms = 4;
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
			if (event.type == sf::Event::MouseWheelMoved)
			{
				if (event.mouseWheel.delta < 0)
					view.zoom(1.1f);
				else if(event.mouseWheel.delta > 0)
					view.zoom(.9f);
			}
        }

        window.clear(sf::Color(35, 38, 32));

		// ****************************
		//          Hotkeys
		// ****************************

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::E) && enemies.size() < 70) {
			enemy.rect.setPosition(generateRandomFloat(enemy.rect.getSize().x + 10, window.getSize().x - 100), generateRandomFloat(enemy.rect.getSize().y + 10, window.getSize().y - 100));
			enemies.push_back(enemy);
		}

		// enemies with target
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::L) && maxtargets > 1)
			maxtargets--;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::H) && maxtargets < enemies.size())
			maxtargets++;
		
		// ****************************
		//          Rooms
		// ****************************
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) && sf::Keyboard::isKeyPressed(sf::Keyboard::R) && rooms < maxRooms)
		{
			rooms++;
			std::vector<Block> newRooms = generateRoom(&window, room.begin(), room.end());
			room.insert(room.end(), newRooms.begin(), newRooms.end());
		}
		// ****************************
		//          Collisions
		// ****************************

		// Enemy and player Collides with block

		for (auto blockIterator = room.begin(); blockIterator != room.end(); blockIterator++) {
			if (!blockIterator->isBarrier)
				continue;
			player.rect.move(player.intersects(*blockIterator) * player.getMovementSpeed());
			
			for (auto iterEnemies = enemies.begin(); iterEnemies != enemies.end(); iterEnemies++)
				iterEnemies->rect.move(iterEnemies->intersects(*blockIterator) * iterEnemies->getMovementSpeed());
		}

		// Projectile Collides with enemy

		for (auto iterProjectiles = projectiles.begin(); iterProjectiles != projectiles.end(); iterProjectiles++) {
			for (auto iterEnemies = enemies.begin(); iterEnemies != enemies.end(); iterEnemies++) {
				if (iterProjectiles->intersects(*iterEnemies) != sf::Vector2f(.0f, .0f)) {
					iterEnemies->takeDamage(msg, iterProjectiles->getAttackDamage(), iterEnemies->rect.getPosition());
					iterProjectiles->destroy = true;
					if (iterEnemies->destroy)
						addHint(hints, hint, "Player destroyed enemy", window.getSize().x);
					msgs.push_back(msg); // damage msg
				}
			}
		}

		// Enemy collides with player (player takes damage)
		if (enemyCollisionClock.getElapsedTime().asSeconds() > 2) {
			for (auto iterEnemies = enemies.begin(); iterEnemies != enemies.end(); iterEnemies++) {
				sf::Vector2f v = player.intersects(*iterEnemies);
				if (v != sf::Vector2f(.0f, .0f) || player.rect.getGlobalBounds().intersects(iterEnemies->rect.getGlobalBounds())) {
					msgs.push_back(player.takeDamage(msg, iterEnemies->getAttackDamage()));
					enemyCollisionClock.restart();
					//player.rect.move(v * (player.getMovementSpeed() * iterEnemies->getMovementSpeed() * 10 ));
				}
			}
		}

        // Fire (space bar)

        if (fireclock.getElapsedTime().asSeconds() >= 10 / player.getProjectile().getRechargeSpeed()) { // for @small@ projectiles
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
        //          Destroying
        // ****************************

        // The end
        if (player.getHp() <= 0 && player.rect.getScale() != sf::Vector2f(0, 0))
            break; // the end of game


		// Level up
		if (enemies.size() == 0)
		{
			level++;
			addHint(hints, hint, "Level up!", window.getSize().x);
			enemy.setHp(enemy.getHp() * 2);
			enemy.setMovementSpeed(generateRandomFloat(1.0f, 1.5));
			enemy.sprite.setScale(1.5, 1.5);
			enemy.rect.setScale(1.6, 1.6);
			for (int i = 0; i < enemiesCount; i++) {
				enemy.rect.setPosition(generateRandomFloat(enemy.rect.getSize().x + 10, window.getSize().x - 100), generateRandomFloat(enemy.rect.getSize().y + 10, window.getSize().y - 100));
				enemies.push_back(enemy);
			}
			player.setMovementSpeed(enemy.getMovementSpeed() * 1.4);
		}

        destroyEntities<Projectile>(projectiles);

        if(destroyEntities<Enemy>(enemies))
            player.destroyedEnemies++;

        destroyEntities<textDisplay>(msgs);

        // ****************************
        //          Drawing
        // ****************************
        window.draw(background);

        // Drawing Player blocks
        for (auto blockIterator = room.begin(); blockIterator != room.end(); blockIterator++) {
            window.draw(blockIterator->rect);
        }
        // Drawing projectiles
        for (auto iterProjectiles = projectiles.begin(); iterProjectiles != projectiles.end(); iterProjectiles++) {
            iterProjectiles->update();
            window.draw(iterProjectiles->rect);
        }

        // Drawing enemies
		int count = 0; // max enemies with target(player)
		for (auto iterEnemies = enemies.begin(); iterEnemies != enemies.end(); iterEnemies++) {
            iterEnemies->update();
			if (count <= maxtargets - 1 ) {
				iterEnemies->setTarget(player.rect);
				count++;
			}
            window.draw(iterEnemies->sprite);
        }

        // Drawing damage
        for (auto textIterator = msgs.begin(); textIterator != msgs.end(); textIterator++) {
            textIterator->update();
            window.draw(textIterator->text);
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
                player.getProjectile().getName() + " | Level: " + std::to_string(level) );
        window.draw(gameInfo);


        // Drawing hints
        for (auto hintIter = hints.begin(); hintIter != hints.end(); hintIter++) {
            window.draw(hintIter->text);
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
    for (auto entityIterator = entities.begin(); entityIterator != entities.end(); entityIterator++) {
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

	for (auto hintIter = hints.begin(); hintIter != hints.end(); hintIter++)
	{
		hintIter->text.move(0, -15);
	}

    hint.text.setString(txt);
    hint.text.setPosition(X_MAX - hint.text.getGlobalBounds().width - 50, 1000);
    hints.push_back(hint);
}


std::vector<Block> generateRoom(sf::RenderWindow* window, std::vector<Block>::iterator blocksBegin, std::vector<Block>::iterator blocksEnd)
{
	int counter = 0;
	std::vector<Block> room;

	int brickSize = 30;
	Block brick(brickSize, brickSize);
	brick.isBarrier = true;
	brick.rect.setFillColor(sf::Color(99, 103, 89, 150));
	
	bool fail = true;
	int fails = 0;
	const int maxFails = 10;
	while (fail)
	{
		room.clear();
		if (fails >= maxFails)
			break;
		int roomSize = generateRandomInt(5, 15);

		int roomStartX = generateRandomInt(brickSize, window->getSize().x - (1 + roomSize) * brickSize)
			, roomStartY = generateRandomInt(brickSize, window->getSize().y - (1 + roomSize)*brickSize);
		int verticalDoorLocation = generateRandomInt(3, roomSize - 2);

		counter = 1;
		while (counter < roomSize) // horizotal
		{
			brick.rect.setPosition(brickSize * counter + roomStartX, roomStartY);
			room.push_back(brick);

			counter++;
		}
		counter = 0;
		while (counter < roomSize)
		{
			brick.rect.setPosition(brickSize * counter + roomStartX, brickSize * roomSize + roomStartY);
			room.push_back(brick);

			counter++;
		}

		// vertical
		counter = 0;
		while (counter < roomSize)
		{
			brick.rect.setPosition(roomStartX, brickSize * counter + roomStartY);
			room.push_back(brick);

			counter++;
		}
		counter = 0;
		while (counter < roomSize + 1)
		{
			if (counter == verticalDoorLocation)
			{
				counter += 2; continue;
			}
			brick.rect.setPosition(brickSize * roomSize + roomStartX, brickSize * counter + roomStartY);
			room.push_back(brick);

			counter++;
		}


		// if some block intersects another
		fail = false;
		for (auto iterRoom = room.begin(); iterRoom != room.end(); iterRoom++)
		{
			for (auto iterBlocks = blocksBegin; iterBlocks != blocksEnd; iterBlocks++)
			{
				if (iterRoom->rect.getGlobalBounds().intersects(iterBlocks->rect.getGlobalBounds()))
				{
					fail = true;
					fails++;
					break;
				}
			}
			if (fail)
				break;
		}
	}
	return room;
}