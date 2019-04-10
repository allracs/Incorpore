#include "../include/Juego.h"
using namespace sf;

Juego::Juego(){
    dimensiones = new int[2];
    dimensiones[0] = 1280;
    dimensiones[1] = 720;
    window = new RenderWindow(VideoMode(dimensiones[0], dimensiones[1]), "Carga Mapa");
    window->setFramerateLimit(60);
    evento = new Event;
    cargaMapa();
    cargarHUD();
    cargaPlayer();
    view.setSize(dimensiones[0], dimensiones[1]);
    view.zoom(0.2f);
    gameLoop();
}

void Juego::gameLoop(){
    while(window->isOpen()){
        procesarEventos();
        procesarColisiones();
        jugador->movimiento();
        hud_principal->compruebaTeclas();
        setView();
        render();
    }
}

void Juego::procesarColisiones(){
    for(int i = 0; i < mapa->getNumColisiones(); i++){
        //INFERIOR
        if(jugador->cuadradoarr().getGlobalBounds().intersects(mapa->getBounds()[i])){
            jugador->setColision(2);
        }

        //SUPERIOR
        if(jugador->cuadradoabaj().getGlobalBounds().intersects(mapa->getBounds()[i])){
            jugador->setColision(1);
        }

        //IZQUIERDA
        if(jugador->cuadradoder().getGlobalBounds().intersects(mapa->getBounds()[i])){
            jugador->setColision(3);
        }

        //DERECHA
        if(jugador->cuadradoizq().getGlobalBounds().intersects(mapa->getBounds()[i])){
            jugador->setColision(4);
        }
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
    hud_principal->setPosicionVida(view.getCenter().x - dimensiones[0]/10 + 4, view.getCenter().y - dimensiones[1]/10);
    hud_principal->setPosicionHabilidades(view.getCenter().x - hud_principal->getPiezaHabilidades().getGlobalBounds().width/2, view.getCenter().y + dimensiones[1]/10 - hud_principal->getPiezaHabilidades().getGlobalBounds().height);
}

void Juego::setColisions(){

}

void Juego::cargarHUD(){
    hud_principal = new Hud();
}

void Juego::mostrarMapaColisiones(){
    cout << endl << "Mapa de colisiones:" << endl;
    cout <<  "------------------------" << endl;
    for(int j = 0; j < mapa->getHeight(); j++){
        for(int k = 0; k < mapa->getWidth(); k++){
            cout << mapa->getColisiones()[j][k];
        }
       cout << endl;
    }
    cout <<  "------------------------" << endl;
}

void Juego::cargaMapa(){
    mapa = new Mapa;
    //mostrarMapaColisiones();
    //setColisions();
}

void Juego::cargaPlayer(){
    jugador = new Jugador;
}

void Juego::render(){
    window->clear(Color(28,17,23,255));
    window->setView(view);
    for(int i = 0; i < mapa->getNumCapas(); i++){
        for(int j = 0; j < mapa->getHeight(); j++){
            for(int k = 0; k < mapa->getWidth(); k++){
                if(mapa->getMapSprite()[i][j][k]!=NULL){
                    window->draw(*(mapa->getMapSprite()[i][j][k]));
                    if(i == 3){
                        window->draw(jugador->getSprite());
                    }
                }
            }
        }
    }

    window->draw(hud_principal->getPiezaVida());
    window->draw(hud_principal->getPiezaHabilidades());

    window->draw(hud_principal->getTextoVida());

    for(int i = 0; i < hud_principal->getCantidadVida(); i++)
    {
        window->draw(hud_principal->getArrayVida().at(i));
    }

    for(int i = 0; i < hud_principal->getCantidadHabilidades(); i++)
    {
        window->draw(hud_principal->getArrayHabilidades().at(i));
    }

    window->display();
}

View Juego::getView(){
    return view;
}
