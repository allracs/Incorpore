
#include "TitleScreen.h"

TitleScreen::TitleScreen()
{
//ctor
}
TitleScreen::~TitleScreen()
{
//dtor
}

void TitleScreen::LoadContent()
{
    if(!font.loadFromFile("KOMIKAX_.ttf"))
        std::cout <<"no se encuentra la fuente " << std::endl;

        text.setFont(font);
        text.setString("TitleScreen");

        keys.push_back(sf::Keyboard::Z);
        keys.push_back(sf::Keyboard::Return);

}
void TitleScreen::UnloadContent()
{
    GameScreen::UnloadContent();

}


void TitleScreen::Update(sf::RenderWIndow &Window, sf::Event event)
{
    input.Update(event);
    if(input.KeyPressed(keys))
     ScreenManager::GetInstance().AddScreen(new SplashScreen);


}
void TitleScreen::Draw(sf::RenderWindow &Window)
{

    Window.draw(text);
    //igual es text en minuscula
}
