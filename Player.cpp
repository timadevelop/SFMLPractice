//
// Created by vtimofeev on 18/06/16.
//

#include "Player.h"

Player::Player()
{

    hp = 20;
    movementSpeed = 2;
    attackDamage = 5;

    mainCircle.setFillColor(sf::Color::Transparent);
    mainCircle.setOutlineColor(sf::Color(52, 73, 94, 150));
    mainCircle.setOutlineThickness(5);
    mainCircle.setRadius(13);
    rect.setOrigin(mainCircle.getOrigin());

    secondCircle.setFillColor(sf::Color(26, 188, 156,150));
    secondCircle.setRadius(4.5);
    thirdCircle.setFillColor(sf::Color(155, 89, 182,150));
    thirdCircle.setRadius(4.5);
    rect.setSize(sf::Vector2f(mainCircle.getRadius()*2,mainCircle.getRadius()*2));
    rect.setPosition(mainCircle.getRadius()*2,mainCircle.getRadius()*2);
    rect.setFillColor(sf::Color::White);
}

Projectile Player::getProjectile() const{
    return projectile;
}

Projectile Player::fire() {
    projectile.rect.setPosition(
            rect.getPosition().x + rect.getSize().x / 2 - projectile.rect.getSize().x / 2,
            rect.getPosition().y + rect.getSize().y / 2 - projectile.rect.getSize().y / 2);
    projectile.rect.setFillColor(sf::Color(rand() % 255, rand() % 255, rand() % 255, 100));

    projectile.directionVector = directionVector;
    return projectile;
}

Projectile Player::fire(sf::RectangleShape projectileTarget){

    projectile.rect.setPosition(
            rect.getPosition().x + rect.getSize().x / 2 - projectile.rect.getSize().x / 2,
            rect.getPosition().y + rect.getSize().y / 2 - projectile.rect.getSize().y / 2);
    projectile.rect.setFillColor(sf::Color(rand() % 255, rand() % 255, rand() % 255, 100));

    sf::Vector2f vec = projectileTarget.getPosition() - rect.getPosition();
    projectile.directionVector = vec / static_cast<float>(sqrt((vec.x*vec.x) + (vec.y*vec.y)));
    return projectile;
}
textDisplay Player::takeDamage(textDisplay& msg, int damage) {

    hp -= damage;
    msg.text.setString(std::to_string(-damage));
    msg.text.setPosition(rect.getPosition());
    msg.text.setColor(sf::Color::Red);
    target = sf::RectangleShape(sf::Vector2f(0,0));

    backAway(movementSpeed*5); // distance
    return msg;
}

void Player::update() {

    sprite.setPosition(rect.getPosition());
    mainCircle.setPosition(rect.getPosition());

    // setting circles inside main circle
    secondCircle.setPosition(
            mainCircle.getPosition().x + mainCircle.getRadius() - secondCircle.getRadius(),
            mainCircle.getPosition().y + ( mainCircle.getRadius() - 2*secondCircle.getRadius() ) / 2
    );
    thirdCircle.setPosition(
            mainCircle.getPosition().x + mainCircle.getRadius() - thirdCircle.getRadius(),
            mainCircle.getPosition().y + mainCircle.getRadius() + (( mainCircle.getRadius() - 2*thirdCircle.getRadius() ) / 2)
    );

    if(target.getPosition() != sf::Vector2f(0,0) && rect.getGlobalBounds().intersects(target.getGlobalBounds()))
    {
        target = sf::RectangleShape(sf::Vector2f(0,0));
        directionVector = sf::Vector2f(0,0);
    };
    updateMovement();
}

void Player::updateMovement() {
    sf::Vector2f emptyVec = sf::Vector2f(0,0);

    // Boost
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
        movementSpeed = normalSpeed * 2;
    else if (movementSpeed > 1)
        movementSpeed = normalSpeed;

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
        target = sf::RectangleShape(emptyVec);
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            directionVector = sf::Vector2f(-1, -1);
        }
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
            directionVector = sf::Vector2f(1, -1);
        }
        else{
            directionVector = sf::Vector2f(0, -1);
        }
        rect.move(directionVector*movementSpeed);
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        target = sf::RectangleShape(emptyVec);
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            directionVector = sf::Vector2f(-1, 1);
        }
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
            directionVector = sf::Vector2f(1, 1);
        }
        else{
            directionVector = sf::Vector2f(0, 1);
        }
        rect.move(directionVector*movementSpeed);
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        target = sf::RectangleShape(emptyVec);
        directionVector = sf::Vector2f(-1, 0);
        rect.move(directionVector*movementSpeed);
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        target = sf::RectangleShape(emptyVec);
        directionVector = sf::Vector2f(1, 0);
        rect.move(directionVector*movementSpeed);
    }
    else if(target.getPosition() != emptyVec)
        rect.move(directionVector*movementSpeed);


    // Rotating a player in motion
    if( sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right) ||
        sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || target.getPosition() != emptyVec)
    {
        if (directionVector.x <= 0)
            rotationFactor--;
        else if (directionVector.x > 0)
            rotationFactor++;
        else if (directionVector.y > 0.5) // Down
            rotationFactor--;
        else if (directionVector.y < -0.5) // Up
            rotationFactor++;
    }
}

void Player::setTarget(sf::RectangleShape r) {
    target = r;
    sf::Vector2f vec = r.getPosition() - rect.getPosition();
    directionVector = vec / static_cast<float>(sqrt((vec.x*vec.x) + (vec.y*vec.y)));
}

void Player::draw(sf::RenderWindow* window){
    sf::Transform transform;
    transform.rotate(rotationAngle*rotationFactor, mainCircle.getPosition().x + mainCircle.getRadius(), mainCircle.getPosition().y + mainCircle.getRadius());

    if(track.size() > 100)
    {
        track.erase(track.begin());
        track.erase(track.begin());
    }
    // drawing track
    for(std::vector<Wall>::iterator it = track.begin(); it != track.end(); it++){
        window->draw(it->circle, it->transform);
    }
    // drawing player
    window->draw(mainCircle);
    window->draw(secondCircle, transform);
    window->draw(thirdCircle, transform);
    if(rotationAngle*rotationFactor == 360 || rotationAngle*rotationFactor == -360)
        rotationFactor = 0;

    if( sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right) ||
        sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || target.getPosition() != sf::Vector2f(0,0))
    {
        Wall wall;
        wall.transform = transform;
        wall.isBarrier = false;
        wall.circle.setRadius(secondCircle.getRadius());
        wall.circle.setPosition(secondCircle.getPosition());
        wall.circle.setFillColor(sf::Color(
                secondCircle.getFillColor().r,secondCircle.getFillColor().b,secondCircle.getFillColor().g,secondCircle.getFillColor().a - 70
        ));
        track.push_back(wall);
        wall.circle.setRadius(thirdCircle.getRadius());
        wall.circle.setPosition(thirdCircle.getPosition());
        wall.circle.setFillColor(sf::Color(
                thirdCircle.getFillColor().r,thirdCircle.getFillColor().b,thirdCircle.getFillColor().g,thirdCircle.getFillColor().a - 70
        ));
        track.push_back(wall);
    }else if(track.size() >= 2)
    {   track.erase(track.begin());
        track.erase(track.begin());
    }
}


Player::~Player()
{ }
