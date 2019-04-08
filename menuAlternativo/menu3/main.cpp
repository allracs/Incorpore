
#include "SFML/Graphics.hpp"
#include <iostream>
#include "Menu.h"
#include <SFML/Audio.hpp>

//using namespace std;

int main()
{
    sf::RenderWindow window(sf::VideoMode(800,600), "SFML VA");
    //window = new sf::RenderWindow(sf::VideoMode(600,600), "SFML VA");
    //screens
    bool estadoMenu = true;
    bool estadoControles = false;
    sf::RectangleShape fondo(sf::Vector2f(400.0f,600.0f));
    fondo.setPosition(250.0f,70.0f);
    sf::Texture texture;
    texture.loadFromFile("menu2.jpeg");
    fondo.setTexture(&texture);
    //sf::Sprite sprite(texture);
    //CONTROLES
    //sf::RectangleShape controles(sf::Vector2f(450.0f,650.0f));
    fondo.setPosition(250.0f,70.0f);
    //controles.setPosition(250.0f,70.0f);
    sf::Texture textureControles;
    textureControles.loadFromFile("controles.png");


   // sf::Music music;
   // if(!music.openFromFile("Menu.ogg"))
     //   return EXIT_FAILURE;
       // music.openFromFile("Menu.ogg");

    Menu menu(window.getSize().x,window.getSize().y);

    while(window.isOpen())
    {
    sf::Event evento;

        while(window.pollEvent(evento))
        {
            switch(evento.type)
            {
            case sf::Event::KeyReleased:
                switch(evento.key.code)
                {

                    case sf::Keyboard::Up:
                    menu.MoverArriba();
                    break;

                    case sf::Keyboard::Down:
                    menu.MoverAbajo();
                    break;

                    /*case sf::Keyboard::Escape:
                   window.draw(fondo);
                   menu.draw(window);

                    break;
                    */
                    case sf::Keyboard::Return:
                        switch(menu.GetPressedItem())
                        {
                            case 0:
                                std::cout <<"El boton de play se ha pulsado" <<std::endl;
                                break;

                            case 1:
                                std::cout <<"El boton de opciones se ha pulsado" <<std::endl;
                                if(textureControles.loadFromFile("controles.png"))
                                    std::cout <<"textura opciones cargada" <<std::endl;
                                estadoMenu = false;
                                estadoControles=true;
                                 menu.borra(window);
                                fondo.setTexture(&textureControles);
                               // controles.setTexture(&textureControles);

                                        switch(evento.key.code)
                                        {
                                            case sf::Keyboard::Escape:
                                                menu.draw(window);
                                            estadoMenu = true;
                                             std::cout <<"Estado de menu a true" <<std::endl;
                                            break;
                                        }

                                break;

                            case 2:
                                std::cout <<"El boton de exit se ha pulsado" <<std::endl;
                                window.close();
                                break;
                        }
                    window.clear();


                    break;

                }
            break;

            case sf::Event::Closed:
                    window.close();
                    break;
            }
        }

        window.clear();
        window.draw(fondo);
       if(estadoMenu==true){menu.draw(window);}
        window.display();

    }

}
