#include "game.h"
using namespace sf;

game::game(){
    window = new RenderWindow(VideoMode(800,600), "Carga Mapa");
    window->setFramerateLimit(60);
    evento = new Event;
    cargaMapa();
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

void game::cargaMapa(){
    Mapa = new mapa;
}

void game::cargaPlayer(){
    jugador = new player;
}

void game::render(){
    window->clear(Color::Magenta);

    for(int i = 0; i < Mapa->getNumCapas(); i++){
        for(int j = 0; j < Mapa->getHeight(); j++){
            for(int k = 0; k < Mapa->getWidth(); k++){
                if(Mapa->getMapSprite()[i][j][k]!=NULL){
                    window->draw(*(Mapa->getMapSprite()[i][j][k]));
                }
            }
        }
    }


    window->draw(jugador->getPlayer());

    window->display();
}
