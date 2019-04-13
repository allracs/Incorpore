
#include "juego.h"
#include <SFML/Graphics.hpp>
#include <stdlib.h>

juego::juego()
{
    //ventana
    window = new sf::RenderWindow(sf::VideoMode(1280,720), "Incorpore");
    //frames
    window->setFramerateLimit(60);

    cargador();

    update();
}

void juego::cargador()
{
    menu_inicial = new menu;
    evento = new sf::Event;
    raton = new sf::Mouse;
}

void juego::update()
{
    while(window->isOpen())
    {
        std::cout << window->getSize().x << " , " << window->getSize().y << std::endl;
        ////std::cout << sel_raton << std::endl;
        eventos_raton();
        procesar_eventos();
        menu_inicial->setColorOp();
        menu_inicial->setPosicion(window->mapPixelToCoords((sf::Vector2i)window->getSize()).x, window->mapPixelToCoords((sf::Vector2i)window->getSize()).y /2);
        render();
    }
}

void juego::procesar_eventos()
{
    while(window->pollEvent(*evento))
    {
        switch(evento->type)
        {
        case sf::Event::Closed:
            window->close();
            break;
        case sf::Event::KeyReleased:
            switch(evento->key.code)
            {
                case sf::Keyboard::Up:
                    if(menu_inicial->opcion_seleccionada() == 0)
                    {
                        menu_inicial->setOpcionMenu(2);
                    }else{
                        menu_inicial->setOpcionMenu(menu_inicial->opcion_seleccionada()-1);
                    }
                    /*
                    if(sel_raton == false && sel_teclado == false)
                    {
                        sel_teclado = true;
                        menu_inicial->setOpcionMenu(0);
                    }
                    */
                    break;

                case sf::Keyboard::Down:
                    if(menu_inicial->opcion_seleccionada() == 2)
                    {
                        menu_inicial->setOpcionMenu(0);
                    }else{
                        menu_inicial->setOpcionMenu(menu_inicial->opcion_seleccionada()+1);
                    }
                    /*
                    if(sel_raton == false && sel_teclado == false)
                    {
                        sel_teclado = true;
                        menu_inicial->setOpcionMenu(0);
                    }
                    */
                    break;
                case sf::Keyboard::Space:
                    if(menu_inicial->opcion_seleccionada() == 1)
                    {
                        menuprincipal = false;
                    }
                    if(menu_inicial->opcion_seleccionada() == 2)
                    {
                        window->close();
                    }
                    break;
                case sf::Keyboard::Escape:
                    if(menuprincipal == true)
                    {
                        window->close();
                    }
                    if(menuprincipal == false){
                        menuprincipal = true;
                    }
                    break;
            }
            break;
                case sf::Event::MouseButtonReleased:
                    if(menu_inicial->opcion_seleccionada() == 1)
                    {
                        menuprincipal = false;
                    }
                    if(menu_inicial->opcion_seleccionada() == 2)
                    {
                        window->close();
                    }
                    break;


        }
    }
}

void juego::eventos_raton()
{

    sf::FloatRect jugar;
    sf::FloatRect opciones;
    sf::FloatRect salir;

    sf::RectangleShape recjugar;


    for(int i = 0; i < 3; i++)
    {
        if(i == 0)
        {
            jugar = menu_inicial->getOpciones().at(i).getGlobalBounds();
            //std::cout << menu_inicial->getOpciones().at(i).getPosition().x << "," << menu_inicial->getOpciones().at(i).getPosition().x << std::endl;
        }
        if(i == 1)
        {
            opciones = menu_inicial->getOpciones().at(i).getGlobalBounds();
        }
        if(i == 2)
        {
            salir = menu_inicial->getOpciones().at(i).getGlobalBounds();
        }
    }

    //menu_inicial->getOpciones().at(i).getGlobalBounds().contains( raton->getPosition().x - window->getPosition().x, raton->getPosition().y - window->getPosition().y)
    sf::Vector2i pixelPos = raton->getPosition(*window);

    sf::Vector2f pPos = window->mapPixelToCoords(pixelPos);

    if(jugar.contains(pPos.x, pPos.y) && menuprincipal == true)
    {
        menu_inicial->setOpcionMenu(0);
        sel_raton = true;
        sel_teclado = false;
    }
    else if(opciones.contains(pPos.x, pPos.y) && menuprincipal == true)
    {
        menu_inicial->setOpcionMenu(1);
        sel_raton = true;
        sel_teclado = false;
    }
    else if(salir.contains(pPos.x, pPos.y) && menuprincipal == true)
    {
        menu_inicial->setOpcionMenu(2);
        sel_raton = true;
        sel_teclado = false;
    }
    /*
    else{
        if(sel_teclado == false){
            menu_inicial->setOpcionMenu(3);
        }
        sel_raton = false;
    }
    */
    recjugar.setSize({opciones.width, opciones.height});


    ////std::cout << raton->getPosition().x - window->getPosition().x << "," << raton->getPosition().y - window->getPosition().y << std::endl;
    //std::cout << recjugar.getSize().x << "," << recjugar.getSize().y << std::endl;


}
/*
void juego::playMusica()
{
//sf::Music musica;
sf::Sound sonido;
sf::SoundBuffer buffer;
    if(buffer.loadFromFile("Menu.ogg"))
        //std::cout << "no va la musiquica"<< std::endl;
//if(!musica->openFromFile("src/Menu.ogg"))
  //          //std::cout << "no va la musiquica"<< std::endl;
  sonido.setBuffer(buffer);
  sonido.play();



}
*/
void juego::render()
{
    window->clear();


    //menu principal
    if(menuprincipal == true)
    {
       // playMusica();
     //   musica->play();
        window->draw(menu_inicial->getFondo());
        window->draw(menu_inicial->getTitulo());
        for(int i = 0; i < 3;i++)
        {
            window->draw(menu_inicial->getOpciones().at(i));
        }
    }

    //menu opciones
    else if (menuprincipal == false)
    {
        window->draw(menu_inicial->getFondOpciones());
    }

    window->display();
}
