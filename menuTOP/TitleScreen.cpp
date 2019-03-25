
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

}
void TitleScreen::UnloadContent()
{


}


void TitleScreen::Update()
{


}
void TitleScreen::Draw(sf::RenderWindow &Window)
{

    Window.draw(text);
    //igual es text en minuscula
}
