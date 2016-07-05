//
// Created by vtimofeev on 01/07/16.
//

#include "MenuScene.h"


MenuScene::MenuScene()
{
    playing = false;
}

void MenuScene::reset() {
    playing = false;
}

int MenuScene::Run(sf::RenderWindow &App)
{
    App.setView(App.getDefaultView());
    sf::Event Event;
    sf::Font Font;
    int menu = 0;
    if (!Font.loadFromFile("src/fonts/invation2000.ttf"))
    {
        std::cerr << "Error loading .ttf" << std::endl;
        return (-1);
    }


    // ***********************
    //          Background
    // ***********************
    sf::VertexArray background(sf::Quads, 4);
    background[0].position = sf::Vector2f(0,0);
    background[1].position = sf::Vector2f(App.getSize().x,0);
    background[2].position = sf::Vector2f(App.getSize().x,App.getSize().y);
    background[3].position = sf::Vector2f(0,App.getSize().y);

    background[0].color = sf::Color( 214, 162, 151 );
    background[1].color = sf::Color( 193, 151, 214 );
    background[2].color = sf::Color( 171, 214, 151 );
    background[3].color = sf::Color( 151, 214, 208 );

    // ***********************
    //          Menu elements
    // ***********************
    sf::Text playText;
    playText.setFont(Font);
    playText.setCharacterSize(30);
    playText.setString("Play");
    playText.setPosition(App.getSize().x/2 - playText.getGlobalBounds().width/2, App.getSize().y/2);


    sf::Text continueText;
    continueText.setFont(Font);
    continueText.setCharacterSize(30);
    continueText.setString("Continue");
    continueText.setPosition(App.getSize().x/2 - continueText.getGlobalBounds().width/2, App.getSize().y/2);

    sf::Text exitText;
    exitText.setFont(Font);
    exitText.setCharacterSize(30);
    exitText.setString("Exit");
    exitText.setPosition(App.getSize().x/2 - exitText.getGlobalBounds().width/2, App.getSize().y/2 + 50);

    // window title
    sf::Text title = sf::Text("Menu", Font, 50);
    title.setPosition(App.getSize().x/2 - title.getGlobalBounds().width/2, 20);
    App.setTitle("Menu");

    while (App.isOpen())
    {
        //Verifying events
        while (App.pollEvent(Event))
        {
            // Window closed
            if (Event.type == sf::Event::Closed) {
                return (-1);
            }
            //Key pressed
            if (Event.type == sf::Event::KeyPressed) {
                switch (Event.key.code) {
                    case sf::Keyboard::Up:
                        menu = 0;
                        break;
                    case sf::Keyboard::Down:
                        menu = 1;
                        break;
                    case sf::Keyboard::Return:
                        if (menu == 0) {
                            //Let's get play !
                            playing = true;
                            return (1);
                        } else {
                            return (-1);
                        }
                        break;
                    default:
                        break;
                }
            }
        }
        if (menu == 0) {
            playText.setScale(1.5, 1.5);
            continueText.setScale(1.5, 1.5);
            exitText.setScale(1, 1);
        } else {
            playText.setScale(1, 1);
            continueText.setScale(1, 1);
            exitText.setScale(1.5, 1.5);
        }

        App.clear();
        //Drawing
        App.draw(background);
        App.draw(title);

        if (playing) {
            App.draw(continueText);
        } else {
            App.draw(playText);
        }
        App.draw(exitText);
        App.display();
    }

    //Never reaching this point normally, but just in case, exit the application
    return (-1);
}


int MenuScene::getResult()
{
    return result;
}