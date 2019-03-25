#include "game.h"
using namespace sf;

game::game(){
    window = new RenderWindow(VideoMode(800,600), "Carga Mapa");
    window->setFramerateLimit(60);
    evento = new Event;
    cargaPlayer();

    gameLoop();
}

void game::gameLoop(){
    while(window->isOpen()){
        procesarEventos();
        jugador->movimiento();
        render();
    }
}

void game::procesarEventos(){

    while(window->pollEvent(*evento)){
        switch(evento->type){

        }
    }

}

void game::cargaPlayer(){
    jugador = new player;
}

void game::render(){
    window->clear(Color::Magenta);

    window->draw(jugador->getPlayer());

    window->display();
}
