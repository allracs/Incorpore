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

    //std::cin.get();
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
        ScreenManager::GetInstance().Update(Window, event);
        ScreenManager::GetInstance().Draw(Window);
        Window.Get
        Window.display();
    }
    return 0;
}
