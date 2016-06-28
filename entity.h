//
// Created by vtimofeev on 18/06/16.
//

#ifndef GAME_ENTITY_H
#define GAME_ENTITY_H

#include "SFML/Graphics.hpp"

enum class Direction{ None, Up, Down, Left, Right };

class entity {
public:
    Direction direction = Direction::None;
    sf::RectangleShape rect;
    sf::Sprite sprite;
    sf::Text text;
    bool intersects(const entity &e) const; // intersection another with entity
    virtual void backAway(int);
};

#endif //GAME_ENTITY_H
