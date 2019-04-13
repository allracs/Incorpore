#include "../include/Juego.h"
#include "../include/Astar.h"
#include "../include/Posicion.h"
#include <vector>
#include <iostream>

using namespace sf;

Juego* Juego::pinstance = 0;

Juego* Juego::Instance(){
    if(pinstance == 0)
        pinstance = new Juego;
    return pinstance;
}

Juego::Juego(){
    dimensiones = Vector2i(1280, 720);
    nEnemigos = 1;

    window = new RenderWindow(VideoMode(dimensiones.x, dimensiones.y), "Incorpore");
    window->setFramerateLimit(60);

    evento = new Event;

    view.setSize(dimensiones.x, dimensiones.y);
    view.zoom(0.2f);

    centrado = false;

    cargaPlayer();
    cargaMapa();
    cargarHUD();
    gameLoop();
    //initStates OJOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO

}

void Juego::cargaPlayer(){
    jugador = new Jugador({150, 50});
    enemigos = new Enemigo*[nEnemigos];
    for(int i = 0; i < nEnemigos; i++){
        enemigos[i] = new Enemigo({150, 100*(i+1)});
    }
    view.setCenter(jugador->getActual()->sprite.getPosition().x, jugador->getActual()->sprite.getPosition().y);
}

void Juego::cargaMapa(){
    mapa = new Mapa;
}

void Juego::cargarHUD(){
    hud = new Hud();
    hud->setPosicionVida(view.getCenter().x - dimensiones.x/10 + 4, view.getCenter().y - dimensiones.y/10);
    hud->setPosicionHabilidades(view.getCenter().x - hud->getPiezaHabilidades().getGlobalBounds().width/2, view.getCenter().y + dimensiones.y/10 - hud->getPiezaHabilidades().getGlobalBounds().height);
}

void Juego::gameLoop(){
    sf::Clock frameClock;

    while(window->isOpen()){
        procesarEventos();
        delta = frameClock.restart().asSeconds();
        jugador->update(delta, *window, mapa->getNumColisiones(), mapa->getBounds());

        manejarIA();
        enemigos[0]->update(delta, *window, mapa->getNumColisiones(), mapa->getBounds(), Posicion(mapa->getPosicionEntidad(*enemigos[0]).x, mapa->getPosicionEntidad(*enemigos[0]).y));

        if(!centrado) {
            setView();
            centrado = true;
        }

        hud->compruebaTeclas();
        setView();
        render();
    }
}
// de maquina updatesfmlevents
void Juego::procesarEventos(){
    while(window->pollEvent(*evento)){

            if(evento->type == sf::Event::Closed)
            this->window->close();
    }
}

void Juego::setView(){
    view.move(jugador->getMovement() * delta);
    hud->move(jugador->getMovement() * delta);
}

//--------DE maquina initStates
void Game::initStates()
{
    //this->states.push(new MainMenuState(this->window, &this->supportedKeys, &this->states));
    this->states.push(new MainMenuState(this->window, &this->states));

    //pushea el primer estado del juego
    //this->states.push(new GameState(this->window, &this->supportedKeys));
}

void Juego::render(){
    window->clear(Color(28,17,23,255));//YA

    window->setView(view);

    mapa->draw(*window, *jugador, *enemigos, nEnemigos);
    hud->draw(*window);
    jugador->drawBoundingBoxes(*window);
    enemigos[0]->drawBoundingBoxes(*window);
    //enemigos[1]->drawBoundingBoxes(*window);

    window->display();
}
//maquina
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


void Juego::manejarIA(){

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
