//
// Created by vtimofeev on 18/06/16.
//
#include "entity.h"


bool entity::intersects(const entity &e) const
{
    return rect.getGlobalBounds().intersects(e.rect.getGlobalBounds());
}


void entity::backAway(float distance){
    rect.move(-directionVector*distance);
}