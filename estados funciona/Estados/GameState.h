#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "State.h"

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


class GameState :
    public State
    {

        private:
        Entity player;
        //funciones
         void initKeybinds();

        public:
            GameState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states);
            virtual ~GameState();

            //funciones
            void endState();

            //  void updateKeybinds(const float& dt);
            void updateInput(const float& dt);
            void update(const float& dt);
           // void render(sf::RenderTarget* target=NULL);
            void render(sf::RenderTarget* target=nullptr);

        //functions

    };
    #endif
