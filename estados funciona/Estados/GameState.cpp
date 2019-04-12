#include "GameState.h"

void GameState::initKeybinds()
{
    this->keybinds.emplace("MOVE_LEFT", this->supportedKeys->at("A"));
    this->keybinds.emplace("MOVE_RIGHT", this->supportedKeys->at("D"));
    this->keybinds.emplace("MOVE_UP", this->supportedKeys->at("W"));
    this->keybinds.emplace("MOVE_DOWN", this->supportedKeys->at("S"));
   //SALIR DEL JUEGO CON ESCAPE ??? FUTURO MENU PAUSA
}


GameState::GameState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states)
: State(window, supportedKeys, states)
{
    this->initKeybinds();
}

GameState::~GameState()
{

}
void GameState::endState()
{
std::cout <<"Se acaba el juego" <<"\n";
}
 //void GameState::updateKeybinds(const float& dt)
 void GameState::updateInput(const float & dt)
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
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_LEFT"))))
        this->player.move(dt,-1.f, 0.f);
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_RIGHT"))))
        this->player.move(dt,1.f, 0.f);
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_UP"))))
        this->player.move(dt,0.f, -1.f);
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_DOWN"))))
        this->player.move(dt,0.f, 1.f);
 }

void GameState::update(const float& dt)
{
     this->updateMousePositions();
    //this->updateKeybinds(dt);
    this->updateInput(dt);

    this->player.update(dt);

}

void GameState::render(sf::RenderTarget* target)
{
        if(!target)
            target = this->window;

            //this->player.render(this->window);
            this->player.render(target);



}
/*
void GameState::updateInput(const float & dt)
{

}
*/



