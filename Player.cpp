//
// Created by vtimofeev on 18/06/16.
//

#include <iostream>
#include "Player.h"

Player::Player()
{
    rect.setSize(sf::Vector2f(32,32));
    rect.setPosition(300, 200);
    rect.setFillColor(sf::Color::White);
    sprite.setTextureRect(sf::IntRect(0, 0, 32, 32));
}

Projectile Player::getProjectile() const{
    return projectile;
}

Projectile Player::fire() {
    projectile.rect.setPosition(
            rect.getPosition().x + rect.getSize().x / 2 - projectile.rect.getSize().x / 2,
            rect.getPosition().y + rect.getSize().y / 2 - projectile.rect.getSize().y / 2);
    projectile.rect.setFillColor(sf::Color(rand() % 255, rand() % 255, rand() % 255));

    projectile.direction = direction;
    return projectile;
}

textDisplay Player::takeDamage(textDisplay& msg, int damage) {

    hp -= damage;
    msg.text.setString(std::to_string(-damage));
    msg.text.setPosition(rect.getPosition());
    msg.text.setColor(sf::Color::Red);

    backAway(damage*10); // distance
    return msg;
 }

void Player::update() {
    sprite.setPosition(rect.getPosition());
    updateMovement();
}

float Player::getMovementSpeed() const
{
    return movementSpeed;
}


// need to fix bug if in updatemovement dont use else
void Player::backAway(int distance)
{
    // changing direction
    if(direction == Direction::Right)
        direction = Direction::Left;
    else if(direction == Direction::Left)
        direction = Direction::Right;
    else if(direction == Direction::Up)
        direction = Direction::Down;
    else if(direction == Direction::Down)
        direction = Direction::Up;

    if(direction == Direction::Right)
        rect.move(distance, 0);
    else if(direction == Direction::Left)
        rect.move(-distance, 0);
    else if(direction == Direction::Up)
        rect.move(0, -distance);
    else if(direction == Direction::Down)
        rect.move(0, distance);


    walkingCounter++;
    if(walkingCounter == 2)
        walkingCounter = 0;
}

void Player::updateMovement() {

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
        movementSpeed = normalSpeed*2;
    else if(movementSpeed > 1)
        movementSpeed = normalSpeed;

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
        sprite.setTextureRect(sf::IntRect(walkingCounter*32, 96, 32, 32));
        rect.move(0, -movementSpeed);
        direction = Direction::Up;
    }

    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
        sprite.setTextureRect(sf::IntRect(walkingCounter*32, 0, 32, 32));
        rect.move(0, movementSpeed);
        direction = Direction::Down;
    }

    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        sprite.setTextureRect(sf::IntRect(walkingCounter*32, 32, 32, 32));
        rect.move(-movementSpeed, 0);
        direction = Direction::Left;
    }

    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        sprite.setTextureRect(sf::IntRect(walkingCounter*32, 64, 32, 32));
        rect.move(movementSpeed, 0);
        direction = Direction::Right;
    }

    walkingCounter++;
    if(walkingCounter == 2)
        walkingCounter = 0;

}


int Player::getHp() const
{
    return hp;
}

void Player::setHp(int value)
{
    hp = value;
}