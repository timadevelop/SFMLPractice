//
// Created by vtimofeev on 19/06/16.
//

#include "textDisplay.h"

textDisplay::textDisplay() {
    text.setColor(sf::Color::White);
    text.setPosition(300,300);
    text.setCharacterSize(20);
    text.setString(str);
}

void textDisplay::update() {

    text.move(moveVector);

    counter++;
    if(counter >= lifeTime)
        destroy = true;
}


void textDisplay::setMoveVector(sf::Vector2f vec)
{
    moveVector = vec;
}