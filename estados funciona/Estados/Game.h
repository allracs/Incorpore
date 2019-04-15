
#ifndef GAME_H
#define GAME_H

#include"SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include"SFML/System.hpp"
#include"SFML/Network.hpp"


#include<iostream>
#include<ctime>
#include<cstdlib>

#include<stack>
#include<vector>
#include<map>


#include "MainMenuState.h"

#include "State.h"

#include "Button.h"

class Game
 {
    private:
        sf::RenderWindow *window;
        sf::Event sfEvent;

        sf::Clock frameClock;
        float dt;

        std::stack<State*> states;

        std::map<std::string, int> supportedKeys;

        void initWindow();
        void initKeys();
        void initStates();


    public:
    Game();
    virtual ~Game();

    //funciones

    //regular
    void endApplication();
    //updates
    void updateDt();
    void procesarEventos();
    void update();
    //render
    void render();

    //nucleo
    void run();
 };

 #endif
