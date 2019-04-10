#include "../include/Juego.h"
using namespace sf;

Juego::Juego(){
    dimensiones = new int[2];
    dimensiones[0] = 1280;
    dimensiones[1] = 720;

    window = new RenderWindow(VideoMode(dimensiones[0], dimensiones[1]), "Carga Mapa");
    window->setFramerateLimit(60);

    evento = new Event;

    view.setSize(dimensiones[0], dimensiones[1]);
    view.zoom(0.2f);

    cargaMapa();
    cargarHUD();
    cargaPlayer();
    gameLoop();
}

void Juego::cargaMapa(){
    mapa = new Mapa;
    //mapa->mostrarMapaColisiones();
    //setColisions();
}

void Juego::cargarHUD(){
    hud = new Hud();
}

void Juego::cargaPlayer(){
    jugador = new Jugador;
}

void Juego::gameLoop(){
    while(window->isOpen()){
        procesarEventos();
        jugador->procesarColisiones(mapa->getNumColisiones(), mapa->getBounds());
        jugador->movimiento();
        hud->compruebaTeclas();
        setView();
        render();
    }
}

void Juego::procesarEventos(){
    while(window->pollEvent(*evento)){
        switch(evento->type){

        }
    }
}

void Juego::setView(){
    view.setCenter(jugador->getSprite().getPosition().x, jugador->getSprite().getPosition().y);
    hud->setPosicionVida(view.getCenter().x - dimensiones[0]/10 + 4, view.getCenter().y - dimensiones[1]/10);
    hud->setPosicionHabilidades(view.getCenter().x - hud->getPiezaHabilidades().getGlobalBounds().width/2, view.getCenter().y + dimensiones[1]/10 - hud->getPiezaHabilidades().getGlobalBounds().height);
}

void Juego::render(){
    window->clear(Color(28,17,23,255));
    window->setView(view);

    mapa->draw(*window, jugador->getSprite());
    hud->draw(*window);

    window->display();
}
