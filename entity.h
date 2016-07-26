//
// Created by vtimofeev on 18/06/16.
//

#ifndef GAME_ENTITY_H
#define GAME_ENTITY_H

#include "SFML/Graphics.hpp"

class entity {
public:
	sf::Vector2f directionVector;
	sf::RectangleShape rect;
	sf::Sprite sprite;
	sf::Text text;
	sf::Vector2f intersects(const entity &e);
	virtual void backAway(float);
};
#endif //GAME_ENTITY_H
