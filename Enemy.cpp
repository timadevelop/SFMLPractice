//
// Created by vtimofeev on 19/06/16.
//


#include "Enemy.h"

Enemy::Enemy()
{
    hp = 2;
    attackDamage = 2;
    movementSpeed = .5;
    rect.setSize(sf::Vector2f(32,32));
    rect.setPosition(0, 33);
    rect.setFillColor(sf::Color::White);
    sprite.setTextureRect(sf::IntRect(0, 0, 32, 32));
}


void Enemy::update() {
    sprite.setPosition(rect.getPosition());
    updateMovement();
}


void Enemy::updateMovement() {

    if(direction == Direction::Right)
    {
        sprite.setTextureRect(sf::IntRect(walkingCounter*32, 64, 32, 32));
        rect.move(movementSpeed, 0);
    }

    if(direction == Direction::Left)
    {
        sprite.setTextureRect(sf::IntRect(walkingCounter*32, 32, 32, 32));
        rect.move(-movementSpeed, 0);
    }

    if(direction == Direction::Up)
    {
        sprite.setTextureRect(sf::IntRect(walkingCounter*32, 96, 32, 32));
        rect.move(0, -movementSpeed);
    }

    if(direction == Direction::Down)
    {
        sprite.setTextureRect(sf::IntRect(walkingCounter*32, 0, 32, 32));
        rect.move(0, movementSpeed);
    }

    walkingCounter++;
    if(walkingCounter == 2)
        walkingCounter = 0;


    // simple ai
    if(counter++ >= movementLength)
    {
        switch (generateRandom(10))
        {
            case 1: direction = Direction::Right;
                break;
            case 2: direction = Direction::Left;
                break;
            case 3: direction = Direction::Up;
                break;
            case 4: direction = Direction::Down;
                break;
            default: direction = Direction::None; // 60% of time will have no direction
        }
        counter = 0;
    }

}
