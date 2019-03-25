
#ifndef SPLASHSCREEN_H
#define SPLASHSCREEN_H

#include "GameScreen.h"
#include <SFML/Graphics.hpp>

#include <string>
#include <iostream>

class SplashScreen : public GameScreen
{
    public:
            SplashScreen();
            ~SplashScreen();

             void LoadContent();
             void UnloadContent();
             void Update();
             void Draw(sf::RenderWindow &Window);
    protected:
    private:
       // sf::String text;
        sf::Text text;
        sf::Font font;

};
#endif //splascreen_h
