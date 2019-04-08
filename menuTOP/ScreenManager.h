#ifndef SCREENMANAGER_H
#define SCREENMANAGER_H

#include <string>
#include <iostream>
#include"GameScreen.h"
#include"SplashScreen.h"
#include"TitleScreen.h"
#include"FadeAnimation.h"



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
        float GetAlpha();

        //void GetFrameTime();

        protected:
        private:
            ScreenManager();
            ScreenManager(ScreenManager const&);
            void operator=(ScreenManager const&);

            //void Transition(sf::RenderWindow &Window);
            void Transition(sf::RenderWindow &Window);
            bool transition;
           // std::string text;
            FadeAnimation fade;

            GameScreen *newScreen;

};
#endif
