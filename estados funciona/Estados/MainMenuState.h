#ifndef MAINMENUSTATE_H
#define MAINMENUSTATE_H

#include "GameState.h"
#include "Button.h"

class MainMenuState :
    public State
    {

        private:
        //variables
        sf::RectangleShape background;
               //funciones
         void initKeybinds();

        public:
            MainMenuState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys);
            virtual ~MainMenuState();

            //funciones
            void endState();

            //  void updateKeybinds(const float& dt);
            void updateInput(const float& dt);
            void update(const float& dt);
           // void render(sf::RenderTarget* target=NULL);
            void render(sf::RenderTarget* target=nullptr);

    };
#endif
