//
// Created by vtimofeev on 19/06/16.
//


#include "Enemy.h"



Enemy::Enemy()
{
    hp = 2;
    attackDamage = 2;
	movementSpeed = generateRandomFloat(.5f, 1.0f);
    rect.setSize(sf::Vector2f(32,32));
    rect.setPosition(0, 17);
    rect.setFillColor(sf::Color::White);
    sprite.setTextureRect(sf::IntRect(0, 0, 32, 32));
    sprite.setScale(0.7, 0.7);
    rect.setScale(0.7, 0.7);
}


void Enemy::update() {
    sprite.setPosition(rect.getPosition());
    updateMovement();
}


void Enemy::setTarget(sf::RectangleShape r) {
	target = r;
	sf::Vector2f vec = r.getPosition() - rect.getPosition();
	float length = static_cast<float>(sqrt((vec.x*vec.x) + (vec.y*vec.y)));
	directionVector = sf::Vector2f(vec.x / length * 2, vec.y / length * 2);
}


void Enemy::updateMovement(){


	// simple ai
    if(target.getPosition() == sf::Vector2f(.0f, .0f) && counter++ >= movementLength)
    {
        switch (generateRandom(10))
        {
            case 1: directionVector = sf::Vector2f(1, 0);
                break;
            case 2: directionVector = sf::Vector2f(-1, 0);
                break;
            case 3: directionVector = sf::Vector2f(0, -1);
                break;
            case 4: directionVector = sf::Vector2f(0, 1);
                break;
            default: directionVector = sf::Vector2f(0,0); // 60% of time will have no direction
        }
        counter = 0;
    }



	if (directionVector.x < -.5f) // Left
	{
		sprite.setTextureRect(sf::IntRect(walkingCounter * 32, 32, 32, 32));
	}
	else if (directionVector.x > .5f) // Right
	{
		sprite.setTextureRect(sf::IntRect(walkingCounter * 32, 64, 32, 32));
	}
    else if(directionVector.y < 0) // Up
    {
        sprite.setTextureRect(sf::IntRect(walkingCounter*32, 96, 32, 32));
    }
    else if(directionVector.y > 0) // Down
    {
        sprite.setTextureRect(sf::IntRect(walkingCounter*32, 0, 32, 32));
    }
    else{
        sprite.setTextureRect(sf::IntRect(0, 0, 32, 32));
    }

    rect.move(directionVector * movementSpeed);
    changeWalkingSprite();
}