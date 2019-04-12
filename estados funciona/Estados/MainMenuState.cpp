#include "MainMenuState.h"

void MainMenuState::initKeybinds()
{
//OJO
/*
    this->keybinds.emplace("MOVE_LEFT", this->supportedKeys->at("A"));
    this->keybinds.emplace("MOVE_RIGHT", this->supportedKeys->at("D"));
    this->keybinds.emplace("MOVE_UP", this->supportedKeys->at("W"));
    this->keybinds.emplace("MOVE_DOWN", this->supportedKeys->at("S"));
    */
    this->keybinds.emplace("CLOSE", this->supportedKeys->at("Escape"));


}


MainMenuState::MainMenuState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states)
: State(window, supportedKeys, states)
{
    this->initFonts();
    this->initKeybinds();
    this->initButtons();


    this->background.setSize(sf::Vector2f(window->getSize().x, window->getSize().y));
    this->background.setFillColor(sf::Color::Magenta);
}

MainMenuState::~MainMenuState()
{
   // delete this->gamestate_btn;
   auto it = this->buttons.begin();
   for(it = this->buttons.begin(); it !=this->buttons.end(); ++it)
   {
        delete it->second;
   }
}

void MainMenuState::updateButtons()
{
    //actualiza todos los botones del estado y controla lo que hacen
    for(auto &it : this->buttons)
    {
        it.second->update(this->mousePosView);
    }

    //Nueva partida
     if(this->buttons["GAME_STATE"]->isPressed())
    {
        //this->states->push(new MainMenuState(this->window, &this->supportedKeys, &this->states));
        this->states->push(new GameState(this->window, this->supportedKeys, this->states));
    }
     //para salir del juego
    if(this->buttons["EXIT_STATE"]->isPressed())
    {
        this->quit=true;
    }
}

void MainMenuState::endState()
{
std::cout <<"Saliendo del estado de menu" <<"\n";
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


    this->updateButtons();


   // this->gamestate_btn->update(this->mousePosView);

    /*
    system("cls");
    std::cout <<this->mousePosView.x<< " "<< this->mousePosView.y << "\n";
*/

}

void MainMenuState::render(sf::RenderTarget* target)
{
        if(!target)
            target = this->window;

            //this->player.render(this->window);
            target->draw(this->background);

           // this->gamestate_btn->render(target);

           this->renderButtons(target);



}
void MainMenuState::initButtons()
{
    ///OJO
    /*
    this->gamestate_btn = new Button(100,100,150,50,
    &this->font, "Jugarr",
    sf::Color(70,70,70,200), sf::Color(150,150,150,255),sf::Color(20,20,20,200));
    */
     this->buttons["GAME_STATE"] = new Button(100,100,150,50,
    &this->font, "Jugarrr",
    sf::Color(70,70,70,200), sf::Color(150,150,150,255),sf::Color(20,20,20,200));

    this->buttons["EXIT_STATE"] = new Button(100,300,150,50,
    &this->font, "Salir",
    sf::Color(100,100,100,200), sf::Color(150,150,150,255),sf::Color(20,20,20,200));
}



void MainMenuState::renderButtons(sf::RenderTarget* target)
{

    for(auto &it : this->buttons)
    {
        it.second->render(target);
    }
}

void MainMenuState::initFonts()
{
    //letrasmenu.ttf
    if(!this->font.loadFromFile("letrasmenu.ttf"))
    {
        throw("ERROR:MAINMENUSTATE:NO SE HA CARGADO LA FUENTE");
    }

}
/*
void GameState::updateInput(const float & dt)
{

}
*/
