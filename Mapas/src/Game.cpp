#include "../include/Game.h"
using namespace sf;

game::game(){
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

void game::gameLoop(){
    while(window->isOpen()){
        procesarEventos();
        procesarColisiones();
        jugador->movimiento();
        hud_principal->compruebaTeclas();
        setView();
        render();
    }
}

void game::procesarColisiones(){

    for(int i = 0; i < mapa->getNumColisiones(); i++){
        //INFERIOR
        if(jugador->cuadradoarr().getGlobalBounds().intersects(colisiones[i])){
            jugador->setColision(2);
        }

        //SUPERIOR
        if(jugador->cuadradoabaj().getGlobalBounds().intersects(colisiones[i])){
            jugador->setColision(1);
        }

        //IZQUIERDA
        if(jugador->cuadradoder().getGlobalBounds().intersects(colisiones[i])){
            jugador->setColision(3);
        }

        //DERECHA
        if(jugador->cuadradoizq().getGlobalBounds().intersects(colisiones[i])){
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
    view.setCenter(jugador->getSprite().getPosition().x, jugador->getSprite().getPosition().y);
    hud_principal->setPosicionVida(view.getCenter().x - dimensiones[0]/10 + 4, view.getCenter().y - dimensiones[1]/10);
    hud_principal->setPosicionHabilidades(view.getCenter().x - hud_principal->getPiezaHabilidades().getGlobalBounds().width/2, view.getCenter().y + dimensiones[1]/10 - hud_principal->getPiezaHabilidades().getGlobalBounds().height);
}

void game::setColisions(){
    colisiones = new FloatRect[mapa->getNumColisiones()];
    Sprite box;
    int n = 0;
    for(int capa = 0; capa < mapa->getNumCapas(); capa++){
        for(int alto = 0; alto < mapa->getHeight(); alto++){
            for(int ancho = 0; ancho < mapa->getWidth(); ancho++){
                    if(n < mapa->getNumColisiones() && mapa->getColisiones()[alto][ancho] == true && mapa->getMapSprite()[capa][alto][ancho] != NULL){
                        box = *mapa->getMapSprite()[capa][alto][ancho];
                        colisiones[n] = box.getGlobalBounds();
                        n++;
                    }

            }
        }
    }
}

void game::cargarHUD(){
    hud_principal = new Hud();
}

void game::mostrarMapaColisiones(){
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

void game::cargaMapa(){
    mapa = new Mapa;
    mostrarMapaColisiones();
    setColisions();
}

void game::cargaPlayer(){
    jugador = new Player;
}

void game::render(){
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

View game::getView(){
    return view;
}
