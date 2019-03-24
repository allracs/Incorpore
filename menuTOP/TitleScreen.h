
#ifndef TITLESCREEN_H
#define TITLESCREEN_H

#include "GameScreen.h"
#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>



class TitleScreen : public GameScreen
{
    public:
            TitleScreen();
            ~TitleScreen();

             void LoadContent();
             void UnloadContent();
             void Update();
             void Draw(sf::RenderWindow &Window);
    protected:
    private:
        sf::Text text;
        sf::Font font;

};
#endif //splascreen_h
