
#include "juego.h"

juego::juego()
{
    window = new sf::RenderWindow(sf::VideoMode(800,600), "Colisiones");
    window->setFramerateLimit(60);

    cargador_mapa();

    cargador_objetos();

    cargador_jugador();

    cargador_enemigo();

    cargar_hud();

    game_loop();

}

void juego::game_loop()
{
    while(window->isOpen())
    {
        personaje->movimiento();
        procesar_eventos();
        procesar_colisiones();
        movimiento_enemigo();
        render();
    }
}

void juego::procesar_colisiones()
{
    //COLISIONES MAPA


    //SUPERIOR
    if(personaje->getJugador().getGlobalBounds().intersects(pared_superior->getParedSuperior().getGlobalBounds()))
    {

        if(personaje->getJugador().getPosition().y > pared_superior->getParedSuperior().getPosition().y)
        {

            arriba = false;
        }
    }
    else{ arriba = true;}


    //INFERIOR
    if(personaje->getJugador().getGlobalBounds().intersects(pared_inferior->getParedInferior().getGlobalBounds()))
    {

        if(personaje->getJugador().getPosition().y < pared_inferior->getParedInferior().getPosition().y)
        {

            abajo = false;
        }
    }
    else{ abajo = true;}


    //DERECHA
    if(personaje->getJugador().getGlobalBounds().intersects(pared_derecha->getParedDerecha().getGlobalBounds()))
    {

        if(personaje->getJugador().getPosition().x < pared_derecha->getParedDerecha().getPosition().x)
        {

            derecha = false;
        }
    }
    else{ derecha = true;}


    //IZQUIERDA
    if(personaje->getJugador().getGlobalBounds().intersects(pared_izquierda->getParedIzquierda().getGlobalBounds()))
    {

        if(personaje->getJugador().getPosition().x > pared_izquierda->getParedIzquierda().getPosition().x)
        {

            izquierda = false;
        }
    }
    else{ izquierda = true;}


    //COLISIONES COLUMNA
    sf::FloatRect box_personaje = personaje->getJugador().getGlobalBounds();
    sf::FloatRect box_columna = columna->getColumna().getGlobalBounds();



        //INFERIOR
        if(personaje->cuadradoarr().getGlobalBounds().intersects(box_columna))
        {
            std::cout << "choca pared inferior" << std::endl;
            personaje->setColision(2);
        }

        //SUPERIOR
        if(personaje->cuadradoabaj().getGlobalBounds().intersects(box_columna))
        {
            std::cout << "choca pared inferior" << std::endl;
            personaje->setColision(1);
        }

        //IZQUIERDA
        if(personaje->cuadradoder().getGlobalBounds().intersects(box_columna))
        {
            std::cout << "choca pared izquieda" << std::endl;
            personaje->setColision(3);
        }

        //DERECHA
        if(personaje->cuadradoizq().getGlobalBounds().intersects(box_columna))
        {
            std::cout << "choca pared derecha" << std::endl;
            personaje->setColision(4);
        }


    //COLISIONES ENEMIGO
    if(personaje->getJugador().getGlobalBounds().intersects(monstruo->getEnemigo().getGlobalBounds()))
    {
        //colisiona por la derecha
        if(personaje->getJugador().getPosition().x > monstruo->getEnemigo().getPosition().x && monstruo->getEnemigo().getFillColor() == sf::Color::Red)
        {
            if(personaje->getVida() > 0)
            {
                personaje->danio(1);
            }
        }
        //colisiona por la izquierda
        if(personaje->getJugador().getPosition().x < monstruo->getEnemigo().getPosition().x && monstruo->getEnemigo().getFillColor() == sf::Color::Red)
        {
            if(personaje->getVida() > 0)
            {
                personaje->danio(2);
            }
        }
        //colisiona por arriba
        if(personaje->getJugador().getPosition().y < monstruo->getEnemigo().getPosition().y && monstruo->getEnemigo().getFillColor() == sf::Color::Red)
        {
            if(personaje->getVida() > 0)
            {
                personaje->danio(3);
            }
        }
        //colisiona por debajo
        if(personaje->getJugador().getPosition().y > monstruo->getEnemigo().getPosition().y && monstruo->getEnemigo().getFillColor() == sf::Color::Red)
        {
            if(personaje->getVida() > 0)
            {
                personaje->danio(4);
            }
        }

    }


    //COLISIONES OBJETOS
    if(borrado != true)
    {
        if(personaje->getJugador().getGlobalBounds().intersects(pocion->getObjeto().getGlobalBounds()))
        {
            personaje->setVida();
            pocion->~objetos();
            borrado = true;
        }
    }
}

void juego::procesar_eventos()
{
    while(window->pollEvent(*evento))
    {
        /*
        switch(evento->type)
        {

        case sf::Event::KeyPressed:
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            {
                if(izquierda == true)
                {
                    personaje->move_izq();
                }
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            {
                if(derecha == true)
                {
                    personaje->move_der();
                }
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
            {
                if(abajo == true)
                {
                    personaje->move__abaj();
                }
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
            {
                if(arriba == true)
                {
                   personaje->move__arr();
                }
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
            {
                monstruo->estado_enemigo();
            }
            break;
        }
        */
    }

}

void juego::cargador_mapa()
{
    pared_superior = new mapa;
    pared_inferior = new mapa;
    pared_derecha = new mapa;
    pared_izquierda = new mapa;
    columna = new mapa;
}

void juego::cargador_jugador()
{
    personaje = new jugador;
    evento = new sf::Event;
}

void juego::cargador_enemigo()
{
    monstruo = new enemigo;
}

void juego::cargador_objetos()
{
    pocion = new objetos;
}

void juego::cargar_hud()
{
    vida_personaje = new hud;
}

void juego::movimiento_enemigo()
{
    monstruo->movimiento_enemigo();
}

void juego::mostrar_vida()
{
    sf::Text vida_enemigo;
    sf::Font fuente;
    fuente.loadFromFile("src/KOMIKAX_.ttf");
    vida_enemigo.setFont(fuente);
    vida_enemigo.setString("Vida enemigo");
    vida_enemigo.setColor(sf::Color::White);
    vida_enemigo.setPosition(400,400);
}

void juego::render()
{
    window->clear();

    //MAPA
    window->draw(pared_superior->getParedSuperior());
    window->draw(pared_inferior->getParedInferior());
    window->draw(pared_derecha->getParedDerecha());
    window->draw(pared_izquierda->getParedIzquierda());
    window->draw(columna->getColumna());

    //OBJETOS
    if(borrado != true)
    {
       window->draw((pocion->getObjeto()));
    }

    //JUGADOR
    window->draw((personaje->cuadradoder()));
    window->draw((personaje->cuadradoarr()));
    window->draw(personaje->getJugador());


    //ENEMIGO
    window->draw(monstruo->getEnemigo());

    //HUD
    window->draw(vida_personaje->updateHUD(personaje->getVida()));

    window->display();
}
