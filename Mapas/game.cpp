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
        procesarColisiones();
        jugador->movimiento();
        setView();
        render();
    }
}

void game::procesarColisiones(){

    //COLISIONES COLUMNA
//    sf::FloatRect box_personaje = jugador->getJugador().getGlobalBounds();

    for(int i = 0; i < Mapa->getNumColisiones(); i++){
    //INFERIOR
    if(jugador->cuadradoarr().getGlobalBounds().intersects(colisiones[i]))
    {
        jugador->setColision(2);
    }

    //SUPERIOR
    if(jugador->cuadradoabaj().getGlobalBounds().intersects(colisiones[i]))
    {
        jugador->setColision(1);
    }

    //IZQUIERDA
    if(jugador->cuadradoder().getGlobalBounds().intersects(colisiones[i]))
    {
        jugador->setColision(3);
    }

    //DERECHA
    if(jugador->cuadradoizq().getGlobalBounds().intersects(colisiones[i]))
    {
        jugador->setColision(4);
    }
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

void game::setColisions(){
    colisiones = new FloatRect[Mapa->getNumColisiones()];
    Sprite box;
    int n = 0;
    for(int capa = 0; capa < Mapa->getNumCapas(); capa++){
        for(int alto = 0; alto < Mapa->getHeight(); alto++){
            for(int ancho = 0; ancho < Mapa->getWidth(); ancho++){
                    if((capa == 4 || capa == 2) && Mapa->getColisiones()[alto][ancho] == true && Mapa->getMapSprite()[capa][alto][ancho] != NULL){
                        box = *Mapa->getMapSprite()[capa][alto][ancho];
                        colisiones[n] = box.getGlobalBounds();
                        n++;
                    }

            }
        }
    }
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
    setColisions();

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
