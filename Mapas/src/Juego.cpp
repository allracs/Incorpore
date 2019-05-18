#include "../include/Juego.h"
#include "../include/Astar.h"
#include "../include/Posicion.h"
#include "../include/Menu.h"
#include "../include/MaquinaEstados.h"
#include <vector>
#include <iostream>

using namespace sf;
using namespace std;

Juego::Juego(MaquinaEstados& maquina, sf::RenderWindow& window, bool cambio): Estado {maquina, window, cambio}
{
    srand(time(0));
    dimensiones = Vector2i(1280, 720);
    nEnemigos = 1;
    nNivel = 1;

    evento = new Event;

    view.setSize(dimensiones.x, dimensiones.y);
    view.zoom(0.2f);

    centrado = false;
    godMode = false;
    hayPortales = false;

    sf::Clock frameClock;


    cargaMapa();
    cargaPlayer();
    cargarHUD();
    //gameLoop();
}


void Juego::pause()
{
    selPausa = 0;

    capaPausa = new sf::RectangleShape;
    capaPausa->setSize({dimensiones.x, dimensiones.y});
    capaPausa->setOrigin(jugador->getSprite().getPosition().x, jugador->getSprite().getPosition().y);
    capaPausa->setPosition({0,0});
    capaPausa->setFillColor(sf::Color(0,0,0,180));

    fuente = new sf::Font;
    fuente->loadFromFile("resources/menu/manaspc.ttf");


    if(jugador->getVidas() <= 0)
    {
        textopausa = new sf::Text;
        textopausa->setFont(*fuente);
        textopausa->setString("- has muerto -");
        textopausa->setScale({0.2,0.2});
        textopausa->setOrigin(textopausa->getGlobalBounds().width/2,0);
        textopausa->setColor(sf::Color::White);
        textopausa->setPosition(view.getCenter().x -20, view.getCenter().y - 40);

        continuar = new sf::Text;
        continuar->setFont(*fuente);
        continuar->setString("reintentar");
        continuar->setScale({0.18,0.18});
        continuar->setColor(sf::Color::Red);
        continuar->setPosition(view.getCenter().x -15, view.getCenter().y - 10);

        salir = new sf::Text;
        salir->setFont(*fuente);
        salir->setString("salir");
        salir->setScale({0.18,0.18});
        salir->setColor(sf::Color::White);
        salir->setPosition(view.getCenter().x -7, view.getCenter().y + 10);

        reintentar = true;
    }
    else
    {
        textopausa = new sf::Text;
        textopausa->setFont(*fuente);
        textopausa->setString("- pausa -");
        textopausa->setScale({0.2,0.2});
        textopausa->setOrigin(textopausa->getGlobalBounds().width/2,0);
        textopausa->setColor(sf::Color::White);
        textopausa->setPosition(view.getCenter().x - 18, view.getCenter().y - 40);

        continuar = new sf::Text;
        continuar->setFont(*fuente);
        continuar->setString("continuar");
        continuar->setScale({0.18,0.18});
        continuar->setColor(sf::Color::Red);
        continuar->setPosition(view.getCenter().x - 19, view.getCenter().y - 10);

        salir = new sf::Text;
        salir->setFont(*fuente);
        salir->setString("salir");
        salir->setScale({0.18,0.18});
        salir->setColor(sf::Color::White);
        salir->setPosition(view.getCenter().x - 11, view.getCenter().y + 10);
    }
}

void Juego::resume()
{
    delete capaPausa;
    delete fuente;
    delete textopausa;
    delete continuar;
    delete salir;
}

void Juego::update()
{
        if(hayPortales){
            portalVerde->update();
            portalMorado->update();
        }

        procesarEventos();
        delta = frameClock.restart().asSeconds();

        for(int i = 0; i < mapa->getAntorchas().size(); i++){
            mapa->getAntorchas().at(i)->update();
        }
        if(pausa == false)
        {
            int arma = jugador->update(delta, m_window, mapa->getNumColisiones(), mapa->getBounds());
            if(arma >= 0){
                hud->cambiaArma(arma);
            }
        hud->compruebaTeclas();
        manejarIA();
        if(jugador->getVidas() < 10 && pocion->isConsumible()){
           if(pocion->consume(jugador->getEntidadHitbox())){
                hud->modificar_vida(1,1);
           }
           //delete pocion;
        }

        if(enemigos.size() > 0){

            for(int i = 0; i < enemigos.size(); i++) {

                if(enemigos.at(i)->getBorrado() == false){

                    //esquinas
                    sf::Vector2i posmap = mapa->getPosicionEntidad(*enemigos[i]);
                    bool **coli = mapa->getColisiones();
                    bool esquinas[4];
                    if(posmap.x-1 != -1 && posmap.y-1 != -1)
                    {
                        esquinas[0] = coli[posmap.y-1][posmap.x-1];
                        esquinas[1] = coli[posmap.y-1][posmap.x+1];
                        esquinas[2] = coli[posmap.y+1][posmap.x-1];
                        esquinas[3] = coli[posmap.y+1][posmap.x+1];
                    }
                    //--------


                    enemigos.at(i)->update(delta, m_window, mapa->getNumColisiones(), mapa->getBounds(),
                                           Posicion(mapa->getPosicionEntidad(*enemigos.at(i)).x, mapa->getPosicionEntidad(*enemigos.at(i)).y),
                                           jugador->getAtaqueHitbox(),
                                           jugador->getArma().getProyectiles(),
                                           esquinas);

                    if(!godMode && jugador->recibeDmg(enemigos.at(i)->getEntidadHitbox(), enemigos.at(i)->getVida())){
                        hud->modificar_vida(1,2);
                    }

                } else {
                    delete enemigos.at(i);
                    enemigos.erase(enemigos.begin()+i);
                }
            }
        }
        else{
            if(!hayPortales){
                portalVerde = new Portal(1,mapa->generaPortales());
                portalMorado = new Portal(2,mapa->generaPortales());
                hayPortales = true;

            }else{

                if(jugador->cogePortal(portalVerde->getPortal().getGlobalBounds())||jugador->cogePortal(portalMorado->getPortal().getGlobalBounds()))
                {
                    colisionaPortal = true;
                    fuente = new sf::Font;
                    fuente->loadFromFile("resources/menu/manaspc.ttf");
                    texportal = new sf::Text;
                    texportal->setFont(*fuente);
                    texportal->setString("pulsa E para avanzar");
                    texportal->setScale(0.2, 0.2);
                    texportal->setPosition(jugador->getSprite().getPosition().x+8, jugador->getSprite().getPosition().y - 56);
                }else{
                    colisionaPortal = false;
                }

                if(pulsaE){
                    if(nNivel < 4){
                        nNivel++;
                    }
                    else{
                        nNivel = 1;
                    }

                    pulsaE = false;
                    entraPortales = true;
                    pausa = false;
                    reintentar = false;
                    hayPortales = false;
                    colisionaPortal = false;
                    delete fuente;
                    delete texportal;
                    delete portalVerde;
                    delete portalMorado;
                    delete mapa;
                    cargaMapa();
                    cargaPlayer();
                    cargarHUD();
                    //std::cout<< jugador->getVidas()<<std::endl;
                }
            }
        }

        if(!centrado) {
            setView();
            centrado = true;
        }

        setView();
        //render();

        if(jugador->getVidas() <= 0)
        {
            jugador->muerteJugador();
            pause();
            pausa = true;
        }


        }
       // frameClock.restart();
}


void Juego::cargaPlayer(){

    if(entraPortales)
    {
        std::cout<< jugador->getVidas()<<std::endl;
        jugador = new Jugador(mapa->generaPosicion(), jugador->getVidas(), jugador->getArma().getOpcion());
        entraPortales = false;
    }
    else
    {
        jugador = new Jugador(mapa->generaPosicion());
    }

    for(int i = 0; i < nEnemigos; i++){
        enemigos.push_back(new Enemigo(mapa->generaPosicion()));
    }

    view.setCenter(jugador->getActual()->sprite.getPosition().x, jugador->getActual()->sprite.getPosition().y);
}



void Juego::cargaMapa(){
    mapa = new Mapa(nNivel);
    pocion = new Consumible(mapa->generaPosicion());
}

void Juego::cargarHUD(){
    hud = new Hud(jugador->getVidas());
    hud->setPosicionVida(view.getCenter().x - dimensiones.x/10 + 2, view.getCenter().y - dimensiones.y/10 + 2);
    hud->setPosicionSwitch(view.getCenter().x + 100, view.getCenter().y - 45);
    hud->setPosicionHabilidades(view.getCenter().x + 22, view.getCenter().y - 70);
}

void Juego::procesarEventos(){
    while(m_window.pollEvent(*evento)){
        switch(evento->type){
            case sf::Event::Closed:
                m_window.close();
                break;
            case sf::Event::MouseButtonPressed:
                if(evento->mouseButton.button == Mouse::Left) {
                    // AÑADIR COOLDOWN AL ATAQUE A MELÉ
                    if(jugador->getArma().getOpcion() == 0){ // SI EL ATAQUE ES A MELEE
                         if(jugador->getCooldownAtaque() >= 1.f) {
                            //std::cout << "COOLDOWN ATAQUE: " << jugador->getCooldownAtaque() << std::endl;
                            jugador->restartCoolDownAtaque();
                            jugador->getArma().atacar(enemigos, enemigos.size());
                            if(jugador->getArma().getOpcion() == 0){
                                jugador->getPuntArma()->empezarAnim();
                            }

                        }
                    } else if(jugador->getArma().getOpcion() == 1) { // SI EL ATAQUE ES A DISTANCIA
                       // std::cout << "ATAQUE A DISTANCIA" << std::endl;
                        jugador->getArma().atacar(enemigos, enemigos.size());
                    }

                }
                break;
            case sf::Event::KeyReleased:
                if(evento->key.code == sf::Keyboard::E && colisionaPortal)
                {
                    pulsaE = true;
                }
                if(evento->key.code == sf::Keyboard::G)
                {
                changeMode();
                }
                if(evento->key.code == sf::Keyboard::Escape)
                {
                    if(pausa == false)
                    {
                        pausa = true;
                        pause();
                    }
                    else
                    {
                        pausa = false;
                        resume();
                    }

                }
                if(evento->key.code == sf::Keyboard::Up || evento->key.code == sf::Keyboard::W)
                {
                    if(selPausa == 1 && pausa)
                    {
                        selPausa = 0;
                        continuar->setColor(sf::Color::Red);
                        salir->setColor(sf::Color::White);
                    }
                }
                if(evento->key.code == sf::Keyboard::Down || evento->key.code == sf::Keyboard::S)
                {
                    if(selPausa == 0 && pausa)
                    {
                        selPausa = 1;
                        continuar->setColor(sf::Color::White);
                        salir->setColor(sf::Color::Red);
                    }


                }
                if(evento->key.code == sf::Keyboard::Space)
                {
                    if(selPausa == 0 && pausa && reintentar)
                    {
                        pausa = false;
                        reintentar = false;
                        m_siguiente = MaquinaEstados::build<Juego>(m_maquina, m_window, true);
                    }
                    if(selPausa == 0 && pausa)
                    {
                        pausa = false;
                    }
                    if(selPausa == 1 && pausa)
                    {
                        pausa = false;
                        view.setSize(dimensiones.x, dimensiones.y);
                        view.setCenter(dimensiones.x/2, dimensiones.y/2);
                        view.zoom(1.0f);
                        m_siguiente = MaquinaEstados::build<Menu>(m_maquina, m_window, true);
                    }
                }



            default: break;

            }

        }
    }

void Juego::setView(){
    view.move(jugador->getMovement() * delta);
    hud->move(jugador->getMovement() * delta);
}


void Juego::draw(){
    m_window.clear(Color(28,17,23,255));
    m_window.setView(view);

    mapa->draw(m_window, *jugador, enemigos, enemigos.size());

    pocion->draw(m_window);
    hud->draw(m_window);
    jugador->drawBoundingBoxes(m_window);
    for(int i = 0; i < enemigos.size(); i++){
        if(enemigos.at(i)->getBorrado() == false)
        enemigos.at(i)->draw(m_window);
    }

    for(int i = 0; i < enemigos.size(); i++){
        if(enemigos.at(i)->getBorrado() == false)
        enemigos.at(i)->drawBoundingBoxes(m_window);
    }
    if(hayPortales){
        portalVerde->draw(m_window);
        portalMorado->draw(m_window);
    }
    if(pausa)
    {
        m_window.draw(*capaPausa);
        m_window.draw(*textopausa);
        m_window.draw(*continuar);
        m_window.draw(*salir);
    }

    if(colisionaPortal && !pausa)
    {
        m_window.draw(*texportal);
    }

    m_window.display();
}

void Juego::changeMode(){
    if(godMode){
        godMode = false;
        std::cout << "GODMODE DESACTIVADO" << std::endl;
    } else {
        godMode = true;
        std::cout << "GODMODE ACTIVADO" << std::endl;
    }
}

void Juego::manejarIA(){

    if(true){   // anyadir clock para que se ejecute cada X tiempo

        Vector2i v = mapa->getPosicionEntidad(*jugador);
        Posicion pos_jugador = Posicion(v.x, v.y);

        // para cada enemigo crear Posicion y llamar a la IA
        // nEnemigos: numero de enemigos en el mapa

        for(int a = 0; a < enemigos.size(); a++){
        if(enemigos.at(a)->getBorrado() == false)
        {
            Vector2i e = mapa->getPosicionEntidad(*enemigos.at(a));
            Posicion pos_enemigo = Posicion(e.x, e.y);
            //asignar posicion al enemigo
            //se crea el astar
            Astar *ia = new Astar(pos_jugador, pos_enemigo, mapa->getColisiones(), mapa->getHeight(), mapa->getWidth());

            //se llama a astar.mapear()

            std::vector<Posicion> path = ia->mapear();

            ////std::cout << path.size() << std::endl;

            enemigos.at(a)->setPath(path);
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
        }

        } //fin for each enemigo
    }
}
