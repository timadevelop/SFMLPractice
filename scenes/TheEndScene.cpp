//
// Created by vtimofeev on 05/07/16.
//

#include "TheEndScene.h"

TheEndScene::TheEndScene() {
}

int TheEndScene::Run(sf::RenderWindow & window) {
    sf::Event event;
    window.setView(window.getDefaultView());

    // ***********************
    //          Background
    // ***********************
//    sf::VertexArray background(sf::Quads, 4);
//    background[0].position = sf::Vector2f(0,0);
//    background[1].position = sf::Vector2f(window.getSize().x,0);
//    background[2].position = sf::Vector2f(window.getSize().x,window.getSize().y);
//    background[3].position = sf::Vector2f(0,window.getSize().y);
//
//    background[0].color = sf::Color( 214, 162, 151 );
//    background[1].color = sf::Color( 193, 151, 214 );
//    background[2].color = sf::Color( 171, 214, 151 );
//    background[3].color = sf::Color( 151, 214, 208 );
//

    sf::Texture texture;
    sf::Sprite background;
    // Background
    if (!texture.loadFromFile("src/back.jpg"))
        std::cerr << "This .jpg file is not found";
    texture.setRepeated(true);
    background.setTexture(texture);
    background.setTextureRect(sf::IntRect(0,0, window.getSize().x, window.getSize().y));

    sf::Font Font;

    if (!Font.loadFromFile("src/fonts/invation2000.ttf"))
    {
        std::cerr << "Error loading ttf" << std::endl;
        return (-1);
    }


    sf::Text exitText;
    exitText.setFont(Font);
    exitText.setCharacterSize(30);
    exitText.setString("Press RETURN to open menu");
    exitText.setPosition(window.getSize().x/2 - exitText.getGlobalBounds().width/2, window.getSize().y/2);

    // window title
    sf::Text title = sf::Text("The end", Font, 50);
    title.setPosition(window.getSize().x/2 - title.getGlobalBounds().width/2, 20);
    std::string resultText = "Your score : " + to_string(result);
    sf::Text result = sf::Text(resultText, Font, 40);
    result.setPosition(window.getSize().x/2 - result.getGlobalBounds().width/2, 90);

    window.setTitle("The end");
    while (window.isOpen())
    {
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                return -1;
            }
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Return) {
                return 0;
            }
        }

        window.clear();
        window.draw(background);
        window.draw(title);
        window.draw(result);
        window.draw(exitText);
        window.display();
    }
    return -1;
}


int TheEndScene::getResult()
{
    return result;
}