#ifndef SCREENMANAGER_H
#define SCREENMANAGER_H

#include <string>
#include <iostream>
#include"GameScreen.h"
#include"SplashScreen.h"
#include"TitleScreen.h"


#define ScreenWidth 800
#define ScreenHeight 600

class ScreenManager
{

    public:
            ~ScreenManager();

        static ScreenManager &GetInstance();

       void Initialize();
       void LoadContent();
       void UnloadContent();
       void Update(sf::RenderWindow &Window, sf::Event event);
       void Draw(sf::RenderWindow &Window);
        void AddScreen(GameScreen *screen);

        protected:
        private:
            ScreenManager();
            ScreenManager(ScreenManager const&);
            void operator=(ScreenManager const&);

           // std::string text;

};
#endif
