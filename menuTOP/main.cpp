#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "ScreenManager.h"

using namespace std;

int main()
{

    sf::RenderWindow Window(sf::VideoMode(ScreenWidth, ScreenHeight, 32), "Prueba de pantalla principal");
   // ScreenManager::GetInstance().SetText("Testing");
    //ScreenManager::GetInstance().DrawText();
   // sf::Shape Fade = sf::RectangleShape (0,0, ScreenWidth,ScreenHeight, sf::Color(255,255,255));
    //Fade = new sf::RectangleShape(0,0);
   // Fade = sf::RectangleShape(0,0);
    // ScreenWidth,ScreenHeight, sf::Color(255,255,255));
    //sf::Shape Fade = sf::RectangleShape(0,0, ScreenWidth, ScreenHeight, sf::Color(255,255,255));
    sf::RectangleShape Fade;
    Fade.setSize(sf::Vector2f(0,0));
    Fade.setFillColor(sf::Color(0,0,0,255 * ScreenManager::GetInstance().GetAlpha()));



    ScreenManager::GetInstance().Initialize();
    ScreenManager::GetInstance().LoadContent();

    Window.setKeyRepeatEnabled(false);
    // EnableKeyRepeat(false);

    while(Window.isOpen())
    {
        sf::Event event;
       // if(Window.GetEvent(event))
       if(Window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed || event.key.code == sf::Keyboard::Escape)
                 Window.close();
                /* if(event.key.code==sf::Keyboard::S)
                    ScreenManager::GetInstance().AddScreen(new SplashScreen);
                    else if(event.key.code ==sf::Keyboard::T)
                    ScreenManager::GetInstance().AddScreen(new TitleScreen);
                    */
        }
        Window.clear();
        //ScreenManager::GetInstance().Update(Window, event);
        ScreenManager::GetInstance().Update(Window, event);

        Fade.setFillColor(sf::Color(0,0,0, 255*ScreenManager::GetInstance().GetAlpha()));
        ScreenManager::GetInstance().Draw(Window);
        Window.draw(Fade);
        Window.display();
    }
    return 0;
}
