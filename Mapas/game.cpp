#include "game.h"
using namespace sf;

game::game(){
    window = new RenderWindow(VideoMode(800,800), "Carga Mapa");
    window->setFramerateLimit(60);
    evento = new Event;
    cargaMapa();
    cargaPlayer();
    view.zoom(0.2f);
    gameLoop();

}

void game::gameLoop(){
    while(window->isOpen()){
        procesarEventos();
        jugador->movimiento();
        setView();
        render();
    }
}

void game::procesarEventos(){

    while(window->pollEvent(*evento)){
        switch(evento->type){

        }
    }

}

void game::setView(){
    view.setCenter(jugador->getPlayer().getPosition().x, jugador->getPlayer().getPosition().y);
}

void game::mostrarMapaColisiones(){
    for(int j = 0; j < Mapa->getHeight(); j++){
        for(int k = 0; k < Mapa->getWidth(); k++){
            cout << Mapa->getColisiones()[j][k];
        }
        cout << endl;
    }
}

void game::cargaMapa(){
    Mapa = new mapa;
    mostrarMapaColisiones();

}

void game::cargaPlayer(){
    jugador = new player;
}

void game::render(){
    window->clear();
    window->setView(view);
    for(int i = 0; i < Mapa->getNumCapas(); i++){
        for(int j = 0; j < Mapa->getHeight(); j++){
            for(int k = 0; k < Mapa->getWidth(); k++){
                if(Mapa->getMapSprite()[i][j][k]!=NULL){
                    window->draw(*(Mapa->getMapSprite()[i][j][k]));
                    if(i == 2){
                        window->draw(jugador->getPlayer());
                    }
                }
            }
        }
    }



    window->display();
}
