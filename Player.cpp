//
// Created by vtimofeev on 18/06/16.
//

#include <iostream>
#include "Player.h"

Player::Player()
{
    hp = 20;
    movementSpeed = 2;
    attackDamage = 5;
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

    projectile.directionVector = directionVector;
    return projectile;
}

textDisplay Player::takeDamage(textDisplay& msg, int damage) {

    hp -= damage;
    msg.text.setString(std::to_string(-damage));
    msg.text.setPosition(rect.getPosition());
    msg.text.setColor(sf::Color::Red);

    backAway(movementSpeed*5); // distance
    return msg;
}

void Player::update() {
    sprite.setPosition(rect.getPosition());
    updateMovement();
}

void Player::updateMovement() {

    // Boost
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
        movementSpeed = normalSpeed*3;
    else if(movementSpeed > 1)
        movementSpeed = normalSpeed;

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
        sprite.setTextureRect(sf::IntRect(walkingCounter*32, 96, 32, 32));

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            directionVector = sf::Vector2f(-1, -1);
        }
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
            directionVector = sf::Vector2f(1, -1);
        }
        else{
            directionVector = sf::Vector2f(0, -1);
        }
        rect.move(directionVector*movementSpeed);
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        sprite.setTextureRect(sf::IntRect(walkingCounter*32, 0, 32, 32));

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            directionVector = sf::Vector2f(-1, 1);
        }
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
            directionVector = sf::Vector2f(1, 1);
        }
        else{
            directionVector = sf::Vector2f(0, 1);
        }
        rect.move(directionVector*movementSpeed);
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        sprite.setTextureRect(sf::IntRect(walkingCounter*32, 32, 32, 32));
        directionVector = sf::Vector2f(-1, 0);
        rect.move(directionVector*movementSpeed);
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        sprite.setTextureRect(sf::IntRect(walkingCounter*32, 64, 32, 32));
        directionVector = sf::Vector2f(1, 0);
        rect.move(directionVector*movementSpeed);
    }
    changeWalkingSprite();
}