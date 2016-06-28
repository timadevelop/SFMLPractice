//
// Created by vtimofeev on 27/06/16.
//

#include <iostream>
#include "Wall.h"

Wall::Wall() {
    rect.setSize(sf::Vector2f(width, height));
    rect.setFillColor(sf::Color::White);
    rect.setPosition(-width, -height);
}

Wall::Wall(float w, float h) : width(w), height(h)
{
    rect.setSize(sf::Vector2f(width, height));
    rect.setFillColor(sf::Color::White);
    if(w > h)
        rect.setPosition(0, -height);
    else if(w < h)
        rect.setPosition(-width, 0);
}