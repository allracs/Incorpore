#include "JuegoState.h"

//includeeeeeeeeeeeeeeeeesss

JuegoState::JuegoState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states)
: State(window, states)//remember he quitado el segundo parametro q era suportedkeys
{
   // this->initKeybinds(); useless
}

//SEGURAMENTE USELESS, LO DEJO DE MOMENTO POR SI ACA
 void GameState::updateInput(const float & dt)
 {
 this->checkForQuit();
 //codigo de los controles useless
  }







JuegoState::~JuegoState(){}

void JuegoState::endState()
{
std::cout <<"Se acaba el juego" <<"\n";
}
