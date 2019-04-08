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
    sf::FloatRect* box_columna = new FloatRect[Mapa->getNumColisiones()];
    sf::Sprite box;
    box = *Mapa->getMapSprite()[4][1][1];
    box_columna[0] = box.getGlobalBounds();
    cout << "FloatRect x: " << box_columna[0].width << endl;
    cout << "FloatRect y: " << box_columna[0].height << endl;
    //cout << "n:" << Mapa->getNumColisiones() << endl;


    //INFERIOR
    if(jugador->cuadradoarr().getGlobalBounds().intersects(box_columna[0]))
    {
        jugador->setColision(2);
    }

    //SUPERIOR
    if(jugador->cuadradoabaj().getGlobalBounds().intersects(box_columna[0]))
    {
        jugador->setColision(1);
    }

    //IZQUIERDA
    if(jugador->cuadradoder().getGlobalBounds().intersects(box_columna[0]))
    {
        jugador->setColision(3);
    }

    //DERECHA
    if(jugador->cuadradoizq().getGlobalBounds().intersects(box_columna[0]))
    {
        jugador->setColision(4);
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
