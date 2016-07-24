//
// Created by vtimofeev on 28/06/16.
//

#include "Organism.h"

textDisplay Organism::takeDamage(textDisplay &msg, int damage, sf::Vector2f rectPosition){
    hp -= damage;
    // Text display
    msg.text.setString(std::to_string(-damage));
    msg.text.setPosition(rectPosition);
    msg.text.setColor(sf::Color::White);
    if (hp <= 0) {
        destroy = true;
    }
    return msg;
}


int Organism::getHp() const
{
    return hp;
}

void Organism::setHp(int value)
{
    hp = value;
}

int Organism::getAttackDamage() const {
    return attackDamage;
}

void Organism::setAttackDamage(int value) {
    attackDamage = value;
}

float Organism::getMovementSpeed() const
{
    return movementSpeed;
}
void Organism::changeWalkingSprite() {

    if (changeSpriteCounter++ == 0) {
        walkingCounter++;
    }
    if (changeSpriteCounter == changeSpritePerFrames) {
        changeSpriteCounter = 0;
    }

    if (walkingCounter == 2)
        walkingCounter = 0;
}