#include "game.h"
using namespace sf;

game::game(){
    window = new RenderWindow(VideoMode(800,800), "Carga Mapa");
    window->setFramerateLimit(60);
    evento = new Event;
    cargaMapa();
    cargar_hud();
    cargaPlayer();
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

    for(int i = 0; i < Mapa->getNumColisiones(); i++){
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
    view.setCenter(jugador->getPlayer().getPosition().x, jugador->getPlayer().getPosition().y);
}

void game::setColisions(){
    colisiones = new FloatRect[Mapa->getNumColisiones()];
    Sprite box;
    int n = 0;
    for(int capa = 0; capa < Mapa->getNumCapas(); capa++){
        for(int alto = 0; alto < Mapa->getHeight(); alto++){
            for(int ancho = 0; ancho < Mapa->getWidth(); ancho++){
                    if(n < Mapa->getNumColisiones() && Mapa->getColisiones()[alto][ancho] == true && Mapa->getMapSprite()[capa][alto][ancho] != NULL){
                        box = *Mapa->getMapSprite()[capa][alto][ancho];
                        colisiones[n] = box.getGlobalBounds();
                        n++;
                    }

            }
        }
    }
}

void game::cargar_hud(){
    hud_principal = new hud;

}

void game::mostrarMapaColisiones(){
    cout << endl << "Mapa de colisiones:" << endl;
    cout <<  "------------------------" << endl;
    for(int j = 0; j < Mapa->getHeight(); j++){
        for(int k = 0; k < Mapa->getWidth(); k++){
            cout << Mapa->getColisiones()[j][k];
        }
       cout << endl;
    }
    cout <<  "------------------------" << endl;
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
    window->clear(Color(28,17,23,255));
    window->setView(view);
    for(int i = 0; i < Mapa->getNumCapas(); i++){
        for(int j = 0; j < Mapa->getHeight(); j++){
            for(int k = 0; k < Mapa->getWidth(); k++){
                if(Mapa->getMapSprite()[i][j][k]!=NULL){
                    window->draw(*(Mapa->getMapSprite()[i][j][k]));
                    if(i == 3){
                        window->draw(jugador->getPlayer());
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
