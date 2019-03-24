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

}
void SplashScreen::UnloadContent()
{


}


void SplashScreen::Update()
{


}
void SplashScreen::Draw(sf::RenderWindow &Window)
{

    Window.draw(text);
    //igual es text en minuscula
}
