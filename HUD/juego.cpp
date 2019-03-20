
#include "juego.h"

juego::juego()
{
    window = new sf::RenderWindow(sf::VideoMode(800,600), "HUD");

    cargar_hud();

    gameloop();
}

void juego::gameloop()
{
    while(window->isOpen())
    {
        procesareventos();

        render();
    }
}

void juego::procesareventos()
{
    while(window->pollEvent(*evento))
    {
        switch(evento->type)
        {
            case sf::Event::KeyPressed:
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
                {
                    hud_principal->modificar_vida(1,1);
                }
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
                {
                    hud_principal->modificar_vida(1,2);
                }
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
                {
                    hud_principal->setHabilidad(1);
                }

            break;

        }
    }
}

void juego::cargar_hud()
{
    hud_principal = new hud;
    evento = new sf::Event;
}

void juego::render()
{
    window->clear();

    window->draw(hud_principal->getPiezaVida());
    window->draw(hud_principal->getPiezaHabilidades());

    window->draw(hud_principal->getTextoVida());

    for(int i = 0; i < hud_principal->getCantidadVida(); i++)
    {
        window->draw(hud_principal->getArrayVida().at(i));
    }
    /*
    for(int i = 0; i < hud_principal->getCantidadHabilidades(); i++)
    {
        window->draw(hud_principal->getArrayHabilidades().at(i));
    }
    */

    window->display();
}
