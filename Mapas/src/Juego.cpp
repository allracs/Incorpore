#include "../include/Juego.h"
#include "../include/Astar.h"
#include "../include/Posicion.h"
#include <vector>
#include <iostream>

using namespace sf;

Juego* Juego::pinstance = 0;

Juego* Juego::Instance(){
    if(pinstance == 0)
        pinstance = new Juego;
    return pinstance;
}

Juego::Juego(){
    dimensiones = Vector2i(1280, 720);
    nEnemigos = 4;

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

void Juego::cargaPlayer(){
    jugador = new Jugador({150, 50});
    enemigos = new Enemigo*[nEnemigos];
    /*
    for(int i = 0; i < nEnemigos; i++){
        enemigos[i] = new Enemigo({150, 100 + 30(i+1)});
    }*/

    enemigos[0] = new Enemigo({150, 100});
    enemigos[1] = new Enemigo({160, 100});
    enemigos[2] = new Enemigo({150, 150});
    enemigos[3] = new Enemigo({160, 160});

    view.setCenter(jugador->getActual()->sprite.getPosition().x, jugador->getActual()->sprite.getPosition().y);
}

void Juego::cargaMapa(){
    mapa = new Mapa;
}

void Juego::cargarHUD(){
    hud = new Hud();
    hud->setPosicionVida(view.getCenter().x - dimensiones.x/10 + 4, view.getCenter().y - dimensiones.y/10);
    hud->setPosicionHabilidades(view.getCenter().x - hud->getPiezaHabilidades().getGlobalBounds().width/2, view.getCenter().y + dimensiones.y/10 - hud->getPiezaHabilidades().getGlobalBounds().height);
}

void Juego::gameLoop(){
    sf::Clock frameClock;

    while(window->isOpen()){
        procesarEventos();
        delta = frameClock.restart().asSeconds();
        jugador->update(delta, *window, mapa->getNumColisiones(), mapa->getBounds());

        manejarIA();

        for(int i = 0; i < nEnemigos; i++) {
            enemigos[i]->update(delta, *window, mapa->getNumColisiones(), mapa->getBounds(), Posicion(mapa->getPosicionEntidad(*enemigos[i]).x, mapa->getPosicionEntidad(*enemigos[i]).y));
        }

        if(!centrado) {
            setView();
            centrado = true;
        }

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
    view.move(jugador->getMovement() * delta);
    hud->move(jugador->getMovement() * delta);
}

void Juego::render(){
    window->clear(Color(28,17,23,255));
    window->setView(view);

    mapa->draw(*window, *jugador, *enemigos, nEnemigos);
    hud->draw(*window);
    jugador->drawBoundingBoxes(*window);

    for(int i = 0; i < nEnemigos; i++){
        enemigos[i]->draw(*window);
    }

    for(int i = 0; i < nEnemigos; i++){
        enemigos[i]->drawBoundingBoxes(*window);
    }

    window->display();
}

void Juego::manejarIA(){

    if(true){   // anyadir clock para que se ejecute cada X tiempo

        Vector2i v = mapa->getPosicionEntidad(*jugador);
        Posicion pos_jugador = Posicion(v.x, v.y);
        int altura = mapa->getHeight();
        int anchura = mapa->getWidth();
        // para cada enemigo crear Posicion y llamar a la IA
        // nEnemigos: numero de enemigos en el mapa

        for(int a = 0; a < nEnemigos; a++){

            Vector2i e = mapa->getPosicionEntidad(*enemigos[a]);
            Posicion pos_enemigo = Posicion(e.x, e.y);

            bool **mapaCol = mapa->getColisiones();

            //--------------------------------------------------------------

            //asignar posicion al enemigo
            //se crea el astar

            Astar *ia = new Astar(pos_jugador, pos_enemigo, mapa->getColisiones(), mapa->getHeight(), mapa->getWidth());

            //se llama a astar.mapear()

            std::vector<Posicion> path = ia->mapear();

            ////std::cout << path.size() << std::endl;


            //---------- CAMINO DEL CENTRO DE CADA COLISIONADOR -------------
            //---------------------------------------------------------------

            Vector2i pos_Col_arr, pos_Col_der, pos_Col_aba, pos_Col_izq;

            enemigos[a]->getPosCol(pos_Col_arr, pos_Col_der, pos_Col_aba, pos_Col_izq);

            Vector2i posXanyadir;
            Posicion next = path.front();
            bool flag = false;
/*
            //ver siguiente pos (next)
            //si next es arriba o abajo:
            if(pos_Col_arr.y - 1 == next.getY() || pos_Col_aba.y + 1 == next.getY()){
                //comprobar que en las esquinas hay una colision
                if(mapaCol[e.x-1][e.y-1] || mapaCol[e.x+1][e.y-1]){
                    //mirar colIzq:
                    //si colIzq esta a la izquierda de pos_enemigo
                    if(pos_Col_izq.x + 1 == pos_enemigo.getX()){
                        //posXanyadir = colIzq
                        posXanyadir = pos_Col_izq;
                        flag = true;
                    }
                    //mirar colDer:
                    //si colDer esta a la derecha de pos_enemigo
                    else if(pos_Col_der.x - 1 == pos_enemigo.getX()){
                        //posXanyadir = colDer
                        posXanyadir = pos_Col_der;
                        flag = true;
                    }

                }
            }
            //si next es izquierda o derecha:
            else if(pos_Col_izq.x + 1 == next.getX() || pos_Col_der.x - 1 == next.getX()){
                if(mapaCol[e.x-1][e.y+1] || mapaCol[e.x+1][e.y+1]){
                    //mirar colArr:
                    //si colArr esta a la arriba de pos_enemigo
                    if(pos_Col_arr.y + 1 == next.getY()){
                        //posXanyadir = colArr
                        posXanyadir = pos_Col_arr;
                        flag = true;
                    }
                    //mirar colAba:
                    //si colAba esta a la abajo de pos_enemigo
                    else if(pos_Col_aba.x - 1 == next.getX()){
                        //posXanyadir = colAba
                        posXanyadir = pos_Col_aba;
                        flag = true;
                    }
                }
            }
*/





            //ver siguiente pos (next)
            //comprobar que en las esquinas hay una colision
            if(e.x-1>=0 && e.y-1>=0 && mapaCol[e.y-1][e.x-1] && e.x == next.getX() && e.y-1 == next.getY()){
                std::cout << "colision arriba izq" << std::endl;
                if(mapaCol[pos_Col_izq.x][pos_Col_izq.y-1]){
                    //posXanyadir = pos_Col_izq;
                    /** TODO: MOVER A LA DERECHA*/
                    flag = true;
                }
            }
            /*if(mapaCol[e.x+1][e.y-1]){
                std::cout << "colision arriba der" << std::endl;
                //si next es arriba o abajo:
                if(pos_Col_arr.y - 1 == next.getY() || pos_Col_aba.y + 1 == next.getY()){

                    //mirar colDer:
                    //si colDer esta a la derecha de pos_enemigo
                    if(pos_Col_der.x - 1 == pos_enemigo.getX()){
                        //posXanyadir = colDer
                        posXanyadir = pos_Col_der;
                        flag = true;
                    }

                }
            }*/





            if(flag){
                    path.insert(path.begin(), Posicion(posXanyadir.x, posXanyadir.y));
            }

            //-------------------------------------------------------------

            enemigos[a]->setPath(path);

            delete ia;


            // SEGUIR EL CAMINO (CON BUCLE INTERPOLADO)
            // mover a enemigos[a] hacia el siguiente punto

            /*
            int flag = true;
            for(int a = 0; a < mapa->getHeight(); a++)
            {
                //std::cout << "  ";
                for(int b = 0; b < mapa->getWidth(); b++)
                {
                    flag = true;
                    for(int c = 0; c < path.size()-1; c++)
                    {
                        if(path.at(c).getX() == b && path.at(c).getY() == a)
                        {
                            //std::cout << "-";
                            flag = false;
                            break;
                        }
                    }
                    if(flag && v.x == b && v.y == a)
                    {
                        //std::cout << "#";
                        flag = false;
                    }
                    if(flag && e.x == b && e.y == a)
                    {
                        //std::cout << "@";
                        flag = false;
                    }
                    if(flag)
                    {
                        if(mapa->getColisiones()[a][b] == 1)
                        {
                            //std::cout << "1";
                        }
                        else
                        {
                            //std::cout << "0";
                        }
                    }
                }
                //std::cout << std::endl;
            }
            */

        } //fin for each enemigo
    }
}
