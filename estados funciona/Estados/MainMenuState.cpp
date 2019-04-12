#include "MainMenuState.h"

void MainMenuState::initKeybinds()
{
    this->keybinds.emplace("MOVE_LEFT", this->supportedKeys->at("A"));
    this->keybinds.emplace("MOVE_RIGHT", this->supportedKeys->at("D"));
    this->keybinds.emplace("MOVE_UP", this->supportedKeys->at("W"));
    this->keybinds.emplace("MOVE_DOWN", this->supportedKeys->at("S"));
   //this->keybinds.emplace("MOVE_LEFT", this->supportedKeys->at("A"));
}


MainMenuState::MainMenuState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys)
: State(window, supportedKeys)
{
    this->initKeybinds();

    this->background.setSize(sf::Vector2f(window->getSize().x, window->getSize().y));
    this->background.setFillColor(sf::Color::Magenta);
}

MainMenuState::~MainMenuState()
{

}
void MainMenuState::endState()
{
std::cout <<"Se acaba el juego" <<"\n";
}
 //void GameState::updateKeybinds(const float& dt)
 void MainMenuState::updateInput(const float & dt)
 {
    this->checkForQuit();
                //ESTO COMENTADO ES SIN BINDEAR
       /* if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        this->player.move(dt,-1.f, 0.f);
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        this->player.move(dt,1.f, 0.f);
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        this->player.move(dt,0.f, -1.f);
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        this->player.move(dt,0.f, 1.f);
    */
    /*
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_LEFT"))))
        this->player.move(dt,-1.f, 0.f);
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_RIGHT"))))
        this->player.move(dt,1.f, 0.f);
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_UP"))))
        this->player.move(dt,0.f, -1.f);
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_DOWN"))))
        this->player.move(dt,0.f, 1.f);
        */

 }

void MainMenuState::update(const float& dt)
{
    this->updateMousePositions();
    //this->updateKeybinds(dt);
    this->updateInput(dt);

    system("cls");
    std::cout <<this->mousePosView.x<< " "<< this->mousePosView.y << "\n";


}

void MainMenuState::render(sf::RenderTarget* target)
{
        if(!target)
            target = this->window;

            //this->player.render(this->window);
            target->draw(this->background);



}
/*
void GameState::updateInput(const float & dt)
{

}
*/
