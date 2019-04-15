#include "../include/Juego.h"
#include "../include/Astar.h"
#include "../include/Posicion.h"
#include <vector>
#include <iostream>

using namespace sf;

Juego::Juego(){

    dimensiones = Vector2i(1280, 720);//de aqui
    window = new RenderWindow(VideoMode(dimensiones.x, dimensiones.y), "Incorpore");//de aqui
    window->setFramerateLimit(60);//de aqui

    evento = new Event; // what ? MIRARRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRR
    //initStates OJOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO
}

void Juego::gameLoop(){
    sf::Clock frameClock;

    while(window->isOpen()){
        procesarEventos(); //DE JUEGO SOLO
        delta = frameClock.restart().asSeconds();//DE AQUI SOLO ¿?¿?

        jugador->update(delta, *window, mapa->getNumColisiones(), mapa->getBounds());//A GAME STATE

        manejarIA();//A GAME STATE
        enemigos[0]->update(delta, *window, mapa->getNumColisiones(), mapa->getBounds(), Posicion(mapa->getPosicionEntidad(*enemigos[0]).x, mapa->getPosicionEntidad(*enemigos[0]).y)); //A GAME STATE

        if(!centrado) { //A GAME STATE
            setView();
            centrado = true;
        }

        hud->compruebaTeclas();//A GAME STATE
        setView();//A gamestate
        render();//DE AMBOS
    }
}
// de maquina updatesfmlevents -> procesarEventos replaceado en el mio para no confundir
void Juego::procesarEventos(){
    while(window->pollEvent(*evento)){

            if(evento->type == sf::Event::Closed)
            this->window->close();
    }
}

//setView pasado a A GAME STATE !!!!!!!!!!!!!!!!!!!!!!



void Juego::render(){
    window->clear(Color(28,17,23,255));//DONE VA AQUI

    //AQUI SOLO EL METODO RENDER DE GAME

    window->setView(view); //esto seria de gamestate

    //mapa->draw(*window, *jugador, *enemigos, nEnemigos);//PASAR A GAMESTATE DONE -- PASADO
   // hud->draw(*window);//GAMESTATE --- pasado
   // jugador->drawBoundingBoxes(*window);//PASAR A GAMESTATE --- pasado
    //enemigos[0]->drawBoundingBoxes(*window);//PASAR A GAMESTATE --- pasado
    //enemigos[1]->drawBoundingBoxes(*window);

      if(!this->states.empty())
                this->states.top()->render();

    window->display();
}
//de maquina
void Juego::update()
{
    this->updateSFMLEvents();

         if(!this->states.empty())
         {
                this->states.top()->update(this->dt);
                if(this->states.top()->getQuit())
                {
                    //en stacks el top es el ultimo insertado en el vector
                    this->states.top()->endState();
                    delete this->states.top();
                    this->states.pop();
                }
            }
            //acaba el programa
            else
            {
                this->endApplication();
                this->window->close();
            }
}
//--------De maquina initStates
void Game::initStates()
{
    //this->states.push(new MainMenuState(this->window, &this->supportedKeys, &this->states));
    this->states.push(new MainMenuState(this->window, &this->states));

    //pushea el primer estado del juego
    //this->states.push(new GameState(this->window, &this->supportedKeys));
}

void Juego::manejarIA(){ // PASAR A GAME STATE --------------- PASADO

    if(true){   // anyadir clock para que se ejecute cada X tiempo

        Vector2i v = mapa->getPosicionEntidad(*jugador);
        Posicion pos_jugador = Posicion(v.x, v.y);

        // para cada enemigo crear Posicion y llamar a la IA
        // nEnemigos: numero de enemigos en el mapa

        for(int a = 0; a < nEnemigos; a++){

            Vector2i e = mapa->getPosicionEntidad(*enemigos[a]);
            Posicion pos_enemigo = Posicion(e.x, e.y);
            //asignar posicion al enemigo
            //se crea el astar
            Astar ia = Astar(pos_jugador, pos_enemigo, mapa->getColisiones(), mapa->getHeight(), mapa->getWidth());

            //se llama a astar.mapear()
            std::vector<Posicion> path = ia.mapear();
            std::cout << path.size() << std::endl;

            enemigos[a]->setPath(path);

            // SEGUIR EL CAMINO (CON BUCLE INTERPOLADO)
            // mover a enemigos[a] hacia el siguiente punto

            int flag = true;
            for(int a = 0; a < mapa->getHeight(); a++)
            {
                std::cout << "  ";
                for(int b = 0; b < mapa->getWidth(); b++)
                {
                    flag = true;
                    for(int c = 0; c < path.size()-1; c++)
                    {
                        if(path.at(c).getX() == b && path.at(c).getY() == a)
                        {
                            std::cout << "-";
                            flag = false;
                            break;
                        }
                    }
                    if(flag && v.x == b && v.y == a)
                    {
                        std::cout << "#";
                        flag = false;
                    }
                    if(flag && e.x == b && e.y == a)
                    {
                        std::cout << "@";
                        flag = false;
                    }
                    if(flag)
                    {
                        if(mapa->getColisiones()[a][b] == 1)
                        {
                            std::cout << "1";
                        }
                        else
                        {
                            std::cout << "0";
                        }
                    }
                }
                std::cout << std::endl;
            }

        } //fin for each enemigo
    }
}
