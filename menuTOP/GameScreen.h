#ifndef GAMESCREEN_H
#define GAMESCREEN_H
#include<SFML/Graphics.hpp>
#include "InputManager.h"

class GameScreen
{
    public:
            GameScreen();
            ~GameScreen();

            virtual void LoadContent();
            virtual void UnloadContent();
            virtual void Update(sf::RenderWindow &Window, sf::Event event);
            virtual void Draw(sf::RenderWindow &Window);
    protected:
        InputManager input;
        std::vector<int> keys;
    private:

};
#endif // gamescreen_h
