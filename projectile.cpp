//
// Created by vtimofeev on 19/06/16.
//

#include "projectile.h"

Projectile::Projectile() {
    rect.setSize(sf::Vector2f(10,10));
    rect.setPosition(0,0);
    rect.setFillColor(sf::Color::White);
}

void Projectile::update() {

    rect.move(directionVector*movementSpeed);
    counterLifeTime++;
    if(counterLifeTime >= lifeTime)
        destroy = true;
}

int Projectile::getAttackDamage() const {
    return attackDamage;
}

void Projectile::setAttackDamage(int value) {
    attackDamage = value;
}

float Projectile::getRechargeSpeed() const {
    return rechargeSpeed;
}

void Projectile::setRechargeSpeed(float seconds)
{
	rechargeSpeed = seconds;
}

std::string Projectile::getName() const {
    return name;
}

void Projectile::setName(std::string str)
{
    name = str;
}