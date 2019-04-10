
#include "hud.h"

hud::hud()
{
    fuente = new sf::Font;
    fuente->loadFromFile("src/coolvetica.ttf");
    vida_personaje = new sf::Text;
    vida_personaje->setFont(*fuente);
}

sf::Text hud::getHud()
{
    return *vida_personaje;
}

sf::Text hud::updateHUD(int vidaPer)
{
    vida_personaje->setString("Vida personaje: " + std::to_string(vidaPer));

    return *vida_personaje;
}
