//
// Created by vtimofeev on 18/06/16.
//
#include "entity.h"
#include <iostream>

sf::Vector2f entity::intersects(const entity &e)
{
	if (!rect.getGlobalBounds().intersects(e.rect.getGlobalBounds()))
		return sf::Vector2f(.0f, .0f);
	

	bool rightCollision = false, leftCollision = false, topCollision = false, bottomCollision = false;

	// current entities states
	sf::Vector2f rectPosition = rect.getPosition();
	sf::Vector2f rectSize = rect.getSize();
	sf::Vector2f entityRectPosition = e.rect.getPosition();
	sf::Vector2f entityRectSize = e.rect.getSize();


	// Collision points on rectangle
	// t/l===== r
	//    =====
	// b  =====

	sf::Vector2f bottomCollisionPoint;
	if (directionVector.x >= 0)
		bottomCollisionPoint = sf::Vector2f(rectPosition.x, rectPosition.y + rectSize.y);
	else
		bottomCollisionPoint = sf::Vector2f(rectPosition.x + rectSize.x, rectPosition.y + rectSize.y);
	
	sf::Vector2f topCollisionPoint;
	if (directionVector.x >= 0)
		topCollisionPoint = rectPosition;
	else
		topCollisionPoint = sf::Vector2f(rectPosition.x + rectSize.x, rectPosition.y);

	sf::Vector2f rightCollisionPoint;
	if (directionVector.y >= 0)
		rightCollisionPoint = sf::Vector2f(rectPosition.x + rectSize.x, rectPosition.y);
	else
		rightCollisionPoint = sf::Vector2f(rectPosition.x + rectSize.x, rectPosition.y + rectSize.y);

	sf::Vector2f leftCollisionPoint;
	if (directionVector.y >= 0)
		leftCollisionPoint = rectPosition;
	else
		leftCollisionPoint = sf::Vector2f(rectPosition.x, rectPosition.y + rectSize.y);

	
	//
	// Finding a collision side
	//
	if (
		e.rect.getGlobalBounds().contains(rightCollisionPoint) &&
		rectPosition.x + rectSize.x >= entityRectPosition.x && 
		rectPosition.x + rectSize.x < entityRectPosition.x + entityRectSize.x) // player on left side
	{
		rightCollision = true;
	}
	else if (
		(e.rect.getGlobalBounds().contains(leftCollisionPoint) )&& //|| e.rect.getGlobalBounds().contains(rectPosition.x + rectSize.x, rectPosition.y)) &&
		rectPosition.x <= entityRectPosition.x + entityRectSize.x &&
		rectPosition.x > entityRectPosition.x) // player on right side
	{
		leftCollision = true;
	}

	if (e.rect.getGlobalBounds().contains(bottomCollisionPoint) && rectPosition.y + rectSize.y >= entityRectPosition.y &&
		rectPosition.y + rectSize.y < entityRectPosition.y + entityRectSize.y) // player on top side
	{
		bottomCollision = true;
	}else if (e.rect.getGlobalBounds().contains(topCollisionPoint) && rectPosition.y <= entityRectPosition.y + entityRectSize.y &&
		rectPosition.y > entityRectPosition.y) // player on bottom side
	{
		topCollision = true;
	}

	//
	// Congiguring a response vector
	//

	sf::Vector2f result(0, 0);
	if (rightCollision)// && directionVector.x >= 0)
		result.x = -directionVector.x;
	else if (leftCollision)// && directionVector.x <= 0)
		result.x = -directionVector.x;
	if (topCollision)// && directionVector.y <= 0)
		result.y = -directionVector.y;
	else if (bottomCollision)// && directionVector.y >= 0)
		result.y = -directionVector.y;
	return result;

}

void entity::backAway(float distance){
    rect.move(-directionVector*distance);
}