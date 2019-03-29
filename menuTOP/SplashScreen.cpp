#include "SplashScreen.h"



SplashScreen::SplashScreen()
{
    //ctor
}
SplashScreen::~SplashScreen()
{
    //dtor
}

void SplashScreen::LoadContent()
{
    if(!font.loadFromFile("KOMIKAX_.ttf"))
        std::cout <<"no se encuentra la fuente " << std::endl;

        text.setFont(font);
        text.setString("SplashScreen");
        // toString("Splashcreen");
        keys.push_back(sf::Keyboard::Z);
        keys.push_back(sf::Keyboard::Return);


}
void SplashScreen::UnloadContent()
{
    GameScreen::UnloadContent();

}


void SplashScreen::Update(sf::RenderWindow &Window, sf::Event event)
{
    input.Update(event);
    if(input.KeyPressed(keys))
     ScreenManager::GetInstance().AddScreen(new TitleScreen);

}
void SplashScreen::Draw(sf::RenderWindow &Window)
{

    Window.draw(text);
    //igual es text en minuscula
}
