#include "../include/Juego.h"
#include "../include/Astar.h"
#include "../include/Posicion.h"
#include "../include/Menu.h"
#include "../include/MaquinaEstados.h"
#include <vector>
#include <iostream>

using namespace sf;
using namespace std;
/*
Juego* Juego::pinstance = 0;

Juego* Juego::Instance(){
    if(pinstance == 0)
        pinstance = new Juego;
    return pinstance;
}
*/
Juego::Juego(MaquinaEstados& maquina, sf::RenderWindow& window, bool cambio): Estado {maquina, window, cambio}
{
    std::cout << "Juego inciado" << std::endl;
    srand(time(0));
    dimensiones = Vector2i(1280, 720);
    nEnemigos = 10;
    /*
    window = new RenderWindow(VideoMode(dimensiones.x, dimensiones.y), "Incorpore");
    m_window.setFramerateLimit(60);
    */
    evento = new Event;

    view.setSize(dimensiones.x, dimensiones.y);
    view.zoom(0.2f);

    centrado = false;
    godMode = false;

    sf::Clock frameClock, iaClock;


    cargaMapa();
    cargaPlayer();
    cargarHUD();
    //gameLoop();
}


void Juego::pause()
{
    std::cout << "Juego pausa" << std::endl;
}

void Juego::resume()
{
    std::cout << "Juego resume" << std::endl;
}

void Juego::update()
{
    procesarEventos();
    delta = frameClock.restart().asSeconds();
    if(interpolation.getElapsedTime().asMilliseconds() > 1000/700 && pausa == false)
    {
        jugador->update(delta, m_window, mapa->getNumColisiones(), mapa->getBounds());
        hud->compruebaTeclas();
        manejarIA();
        if(jugador->getVidas() < 10 && pocion->isConsumible())
        {
            if(pocion->consume(jugador->getEntidadHitbox()))
            {
                hud->modificar_vida(1,1);
            }
            //delete pocion;
        }

        if(enemigos.size() > 0)
        {

            for(int i = 0; i < enemigos.size(); i++)
            {

                if(enemigos.at(i)->getBorrado() == false)
                {
                    //  std::cout << enemigos.size() << std::endl;
                    enemigos.at(i)->update(delta, m_window, mapa->getNumColisiones(), mapa->getBounds(), Posicion(mapa->getPosicionEntidad(*enemigos.at(i)).x, mapa->getPosicionEntidad(*enemigos.at(i)).y), jugador->getAtaqueHitbox());

                    if(!godMode && jugador->recibeDmg(enemigos.at(i)->getEntidadHitbox(), enemigos.at(i)->getVida()))
                    {
                        hud->modificar_vida(1,2);
                    }

                }
                else
                {
                    delete enemigos.at(i);
                    enemigos.erase(enemigos.begin()+i);
                }
            }
        }

        if(!centrado) {
            setView();
            centrado = true;
        }

        setView();
        interpolation.restart();
        //render();
    }
}

void Juego::cargaPlayer(){

    jugador = new Jugador(mapa->generaPosicion());

    for(int i = 0; i < nEnemigos; i++){
        enemigos.push_back(new Enemigo(mapa->generaPosicion()));
    }

    view.setCenter(jugador->getActual()->sprite.getPosition().x, jugador->getActual()->sprite.getPosition().y);
}



void Juego::cargaMapa(){
    mapa = new Mapa;
    pocion = new Consumible(mapa->generaPosicion());
}

void Juego::cargarHUD(){
    hud = new Hud();
    hud->setPosicionVida(view.getCenter().x - dimensiones.x/10 + 2, view.getCenter().y - dimensiones.y/10 + 2);
    hud->setPosicionHabilidades(view.getCenter().x - hud->getPiezaHabilidades().getGlobalBounds().width/2, view.getCenter().y + dimensiones.y/10 - hud->getPiezaHabilidades().getGlobalBounds().height);
}

void Juego::procesarEventos(){
    while(m_window.pollEvent(*evento)){
        switch(evento->type){
            case sf::Event::Closed:
                m_window.close();
                break;
            case sf::Event::MouseButtonPressed:
                if(evento->mouseButton.button == Mouse::Left) {
                    //cout << "HE PULSADO EL BOTÓN"<< endl;
                    jugador->getArma().atacar(0, enemigos, enemigos.size());
                }
                break;
            case sf::Event::KeyPressed:
                if(evento->key.code == sf::Keyboard::G)
                {
                changeMode();
                }
                if(evento->key.code == sf::Keyboard::Escape)
                {
                    if(pausa == false)
                    {
                        pausa = true;
                    }
                    else
                    {
                        pausa = false;
                    }

                }
                default: break;
            }

        }
    }

void Juego::setView(){
    view.move(jugador->getMovement() * delta);
    hud->move(jugador->getMovement() * delta);
}

void Juego::draw(){
    m_window.clear(Color(28,17,23,255));
    m_window.setView(view);

    mapa->draw(m_window, *jugador, enemigos, enemigos.size());

    pocion->draw(m_window);
    hud->draw(m_window);
    jugador->drawBoundingBoxes(m_window);
    /*
    for(int i = 0; i < enemigos.size(); i++){
        if(enemigos.at(i)->getBorrado() == false)
        enemigos.at(i)->draw(m_window);
    }

    for(int i = 0; i < enemigos.size(); i++){
        if(enemigos.at(i)->getBorrado() == false)
        enemigos.at(i)->drawBoundingBoxes(m_window);
    }*/

    m_window.display();
}

void Juego::changeMode(){
    if(godMode){
        godMode = false;
        std::cout << "GODMODE DESACTIVADO" << std::endl;
    } else {
        godMode = true;
        std::cout << "GODMODE ACTIVADO" << std::endl;
    }
}

void Juego::manejarIA(){

    if(iaClock.getElapsedTime().asMilliseconds() >= 0.3){   // anyadir clock para que se ejecute cada X tiempo

        //std::cout << iaClock.getElapsedTime().asSeconds() << std::endl;
        iaClock.restart();
        Vector2i v = mapa->getPosicionEntidad(*jugador);
        Posicion pos_jugador = Posicion(v.x, v.y);

        // para cada enemigo crear Posicion y llamar a la IA
        // nEnemigos: numero de enemigos en el mapa

        for(int a = 0; a < enemigos.size(); a++){
        if(enemigos.at(a)->getBorrado() == false)
        {
            Vector2i e = mapa->getPosicionEntidad(*enemigos.at(a));
            Posicion pos_enemigo = Posicion(e.x, e.y);
            //asignar posicion al enemigo
            //se crea el astar
            Astar *ia = new Astar(pos_jugador, pos_enemigo, mapa->getColisiones(), mapa->getHeight(), mapa->getWidth());

            //se llama a astar.mapear()

            std::vector<Posicion> path = ia->mapear();

            ////std::cout << path.size() << std::endl;

            enemigos.at(a)->setPath(path);
            delete ia;

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
        }

        } //fin for each enemigo
    }
}
