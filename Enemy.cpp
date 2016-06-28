//
// Created by vtimofeev on 19/06/16.
//


#include "Enemy.h"

Enemy::Enemy()
{
    rect.setSize(sf::Vector2f(32,32));
    rect.setPosition(0, 33);
    rect.setFillColor(sf::Color::White);
    sprite.setTextureRect(sf::IntRect(0, 0, 32, 32));
}


textDisplay Enemy::takeDamage(textDisplay &msg, int damage){

    hp -= damage;
    // Text display
    msg.text.setString(std::to_string(-damage));
    msg.text.setPosition(rect.getPosition());
    msg.text.setColor(sf::Color::White);
    if (hp <= 0) {
        destroy = true;
    }
    return msg;
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


int Enemy::getHp() const
{
    return hp;
}

void Enemy::setHp(int value)
{
    hp = value;
}

int Enemy::getAttackDamage() const {
    return attackDamage;
}

void Enemy::setAttackDamage(int value) {
    attackDamage = value;
}

float Enemy::getMovementSpeed() const
{
    return movementSpeed;
}