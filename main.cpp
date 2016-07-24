#include <iostream>
#include <SFML/Graphics.hpp>

using namespace std;

#include "scenes/Scenes.h"


int main()
{
    std::vector<Scene*> screens;
    int screen = 0;

    //Window creation
	auto videoMode = sf::VideoMode::getFullscreenModes()[0];
    sf::RenderWindow App(videoMode, "Game", sf::Style::Fullscreen);
    App.setFramerateLimit(60);
    //Mouse cursor no more visible
    //App.setMouseCursorVisible(false);

    //Screens preparations
    MenuScene* menuScene = new MenuScene;
    screens.push_back(menuScene);
    GameScene* gameLoop = new GameScene(App);
    screens.push_back(gameLoop);
    TheEndScene* endScene = new TheEndScene;
    screens.push_back(endScene);
    //Main loop

    // if returns 0 - menuScene, if 1 - GameScene if 2 ..
    while (screen >= 0)
    {
        screen = screens[screen]->Run(App);
        if(screen == 2) {
            Scene *tmp = screens[1];
            screens[screen]->result = screens[1]->getResult();
            screens[1] = new GameScene(App);
            delete (tmp);
            menuScene->reset();
        }
    }

    while(!screens.empty()) delete screens.back(), screens.pop_back();

    return EXIT_SUCCESS;
}
