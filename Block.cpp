//
// Created by vtimofeev on 27/06/16.
//

#include "Block.h"

Block::Block() {
    rect.setSize(sf::Vector2f(width, height));
    rect.setFillColor(sf::Color::Transparent);
    rect.setPosition(-width, -height);
}

Block::Block(float w, float h) : width(w), height(h)
{
    rect.setSize(sf::Vector2f(width, height));
    rect.setFillColor(sf::Color::Transparent);
    if(w > h)
        rect.setPosition(0, -height);
    else if(w < h)
        rect.setPosition(-width, 0);
}