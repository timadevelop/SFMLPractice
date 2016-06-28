//
// Created by vtimofeev on 18/06/16.
//

#include "entity.h"


bool entity::intersects(const entity &e) const
{
    return rect.getGlobalBounds().intersects(e.rect.getGlobalBounds());
}


void entity::backAway(int distance) {

    // changing direction
    if (direction == Direction::Right)
        direction = Direction::Left;
    else if (direction == Direction::Left)
        direction = Direction::Right;
    else if (direction == Direction::Up)
        direction = Direction::Down;
    else if (direction == Direction::Down)
        direction = Direction::Up;

    if (direction == Direction::Right)
        rect.move(distance, 0);
    else if (direction == Direction::Left)
        rect.move(-distance, 0);
    else if (direction == Direction::Up)
        rect.move(0, -distance);
    else if (direction == Direction::Down)
        rect.move(0, distance);
}