#include "ScreenManager.h"
GameScreen *currentScreen, *newScreen;

ScreenManager &ScreenManager::GetInstance()
{
   static ScreenManager instance;
    return instance;
}

ScreenManager::ScreenManager(){

//ctor
}

ScreenManager::~ScreenManager()
{
//dtor
}
float ScreenManager::GetAlpha()
{
return fade.GetAlpha();
}
//void ScreenManager::Transition(sf::RenderWindow &Window)
void ScreenManager::Transition(sf::RenderWindow &Window)

{
    if(transition)
    {
        fade.Update(Window);
        if(fade.GetAlpha() >=1.0f)
        {
            currentScreen->UnloadContent();
            delete currentScreen;
            currentScreen = newScreen;
            currentScreen->LoadContent();
            newScreen=NULL;
        }
        else if(fade.GetAlpha() <= 0.0f)
        {
            transition=false;
            fade.SetActive(false);
        }
    }
}

void ScreenManager::AddScreen(GameScreen *screen)
{
    transition = true;
    newScreen = screen;
    //ojo
    fade.SetActive(true);
    fade.SetAlpha(0.0f);
}

void ScreenManager::Initialize()
{
    currentScreen = new SplashScreen();
    transition = false;
    sf::Texture image;
    //sprite?
    sf::Vector2f pos;
    //fade.LoadContent("",image,pos);
}

void ScreenManager::LoadContent()
{
    currentScreen->LoadContent();
     sf::Texture image;
    //sprite?
    sf::Vector2f pos;
    fade.LoadContent("",image,pos);
    fade.SetAlpha(0.0f);

}
void ScreenManager::UnloadContent()
{

}
//void ScreenManager::Update(sf::RenderWindow &Window, sf::Event event)
void ScreenManager::Update(sf::RenderWindow &Window, sf::Event event)

{
//clock?=
    if(!transition)
        currentScreen->Update(Window, event);
    //Transition(Window);
    Transition(Window);


}
void ScreenManager::Draw(sf::RenderWindow &Window)
{
    currentScreen->Draw(Window);

}
