#include "../include/Juego.h"
#include "../include/Astar.h"
#include "../include/Posicion.h"
#include <vector>
#include <iostream>

using namespace sf;
using namespace std;

Juego* Juego::pinstance = 0;

Juego* Juego::Instance(){
    if(pinstance == 0)
        pinstance = new Juego;
    return pinstance;
}

Juego::Juego(){
    srand(time(0));
    dimensiones = Vector2i(1280, 720);
    nEnemigos = 3;

    window = new RenderWindow(VideoMode(dimensiones.x, dimensiones.y), "Incorpore");
    window->setFramerateLimit(60);

    evento = new Event;

    view.setSize(dimensiones.x, dimensiones.y);
    view.zoom(0.2f);

    centrado = false;


    cargaMapa();
    cargaPlayer();
    cargarHUD();
    gameLoop();
}

void Juego::cargaPlayer(){

    jugador = new Jugador(mapa->generaPosicion());
    enemigos = new Enemigo*[nEnemigos];

    for(int i = 0; i < nEnemigos; i++){
        enemigos[i] = new Enemigo(mapa->generaPosicion());
    }

    view.setCenter(jugador->getActual()->sprite.getPosition().x, jugador->getActual()->sprite.getPosition().y);
}



void Juego::cargaMapa(){
    mapa = new Mapa;
}

void Juego::cargarHUD(){
    hud = new Hud();
    hud->setPosicionVida(view.getCenter().x - dimensiones.x/10 + 2, view.getCenter().y - dimensiones.y/10 + 2);
    hud->setPosicionHabilidades(view.getCenter().x - hud->getPiezaHabilidades().getGlobalBounds().width/2, view.getCenter().y + dimensiones.y/10 - hud->getPiezaHabilidades().getGlobalBounds().height);
}

void Juego::gameLoop(){
    sf::Clock frameClock;

    while(window->isOpen()){
        procesarEventos();
        delta = frameClock.restart().asSeconds();
        jugador->update(delta, *window, mapa->getNumColisiones(), mapa->getBounds());

        manejarIA();

        for(int i = 0; i < nEnemigos; i++) {
            enemigos[i]->update(delta, *window, mapa->getNumColisiones(), mapa->getBounds(), Posicion(mapa->getPosicionEntidad(*enemigos[i]).x, mapa->getPosicionEntidad(*enemigos[i]).y), jugador->getAtaqueHitbox());
            if(jugador->recibeDmg(enemigos[i]->getEntidadHitbox(), enemigos[i]->getVida())){
                hud->modificar_vida(1,2);
            }

        }

        if(!centrado) {
            setView();
            centrado = true;
        }

        setView();
        render();
    }
}

void Juego::procesarEventos(){
    while(window->pollEvent(*evento)){
        switch(evento->type){
            case sf::Event::Closed:
                window->close();
                break;
            case sf::Event::MouseButtonPressed:
                if(evento->mouseButton.button == Mouse::Left) {
                    cout << "HE PULSADO EL BOTÓN"<< endl;
                    jugador->getArma().atacar(0, enemigos, nEnemigos);
                }
                break;
            default: break;

        }
    }
}

void Juego::setView(){
    view.move(jugador->getMovement() * delta);
    hud->move(jugador->getMovement() * delta);
}

void Juego::render(){
    window->clear(Color(28,17,23,255));
    window->setView(view);

    mapa->draw(*window, jugador, enemigos, nEnemigos);
    hud->draw(*window);
    jugador->drawBoundingBoxes(*window);

    /*
    for(int i = 0; i < nEnemigos; i++){
        enemigos[i]->draw(*window);
    }

    for(int i = 0; i < nEnemigos; i++){
        enemigos[i]->drawBoundingBoxes(*window);
    }*/

    window->display();
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

            ////std::cout << path.size() << std::endl;

            enemigos[a]->setPath(path);

            // SEGUIR EL CAMINO (CON BUCLE INTERPOLADO)
            // mover a enemigos[a] hacia el siguiente punto
            /*
            int flag = true;
            for(int a = 0; a < mapa->getHeight(); a++)
            {
                //std::cout << "  ";
                for(int b = 0; b < mapa->getWidth(); b++)
                {
                    flag = true;
                    for(int c = 0; c < path.size()-1; c++)
                    {
                        if(path.at(c).getX() == b && path.at(c).getY() == a)
                        {
                            //std::cout << "-";
                            flag = false;
                            break;
                        }
                    }
                    if(flag && v.x == b && v.y == a)
                    {
                        //std::cout << "#";
                        flag = false;
                    }
                    if(flag && e.x == b && e.y == a)
                    {
                        //std::cout << "@";
                        flag = false;
                    }
                    if(flag)
                    {
                        if(mapa->getColisiones()[a][b] == 1)
                        {
                            //std::cout << "1";
                        }
                        else
                        {
                            //std::cout << "0";
                        }
                    }
                }
                //std::cout << std::endl;
            }
            */

        } //fin for each enemigo
    }
}
