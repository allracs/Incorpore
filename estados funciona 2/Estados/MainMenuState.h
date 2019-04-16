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
        sf::Font font;
        sf::Font fontTitulo;//falta setear
         sf::Texture *texfondo;
        sf::Sprite *sprfondo;
        sf::Font *titulofuente;
    sf::Text *titulo;
        std::map<std::string, Button*> buttons;



               //funciones
        void initFonts();
         void initKeybinds();
         void initButtons();

        public:
            MainMenuState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states);
            virtual ~MainMenuState();
            void updateButtons();
            //funciones
            void endState();

            //  void updateKeybinds(const float& dt);
            void updateInput(const float& dt);
            void update(const float& dt);

            void renderButtons(sf::RenderTarget* target =nullptr);

           // void render(sf::RenderTarget* target=NULL);
            void render(sf::RenderTarget* target=nullptr);

    };
#endif
