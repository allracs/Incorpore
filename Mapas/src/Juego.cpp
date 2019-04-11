#include "../include/Juego.h"
using namespace sf;

Juego::Juego(){
    dimensiones = Vector2i(1280, 720);

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
    jugador = new Jugador({150, 50});
}

void Juego::gameLoop(){
    sf::Clock frameClock;

    while(window->isOpen()){
        procesarEventos();

        float delta = frameClock.restart().asSeconds();
        jugador->update(delta, *window);

        /*jugador->mover();
        jugador->movimiento();
        jugador->rotacionAtaque(*window);*/
        //jugador->update(delta, *window);

        if(!centrado) {
            setView();
            centrado = true;
        }

        //jugador->procesarColisiones(mapa->getNumColisiones(), mapa->getBounds());

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
    view.setCenter(jugador->getActual()->sprite.getPosition().x, jugador->getActual()->sprite.getPosition().y);
    hud->setPosicionVida(view.getCenter().x - dimensiones.x/10 + 4, view.getCenter().y - dimensiones.y/10);
    hud->setPosicionHabilidades(view.getCenter().x - hud->getPiezaHabilidades().getGlobalBounds().width/2, view.getCenter().y + dimensiones.y/10 - hud->getPiezaHabilidades().getGlobalBounds().height);
}

void Juego::render(){
    window->clear(Color(28,17,23,255));
    window->setView(view);

    mapa->draw(*window, jugador->getSprite());
    hud->draw(*window);
    jugador->drawBoundingBoxes(*window);
    jugador->draw(*window);



    window->display();
}
