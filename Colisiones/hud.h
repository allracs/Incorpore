
#include <SFML/Graphics.hpp>
#include <iostream>

class hud
{
public:
    hud();
    sf::Text getHud();
    sf::Text updateHUD(int);

private:
    sf::Font *fuente;
    sf::Text *vida_personaje;
};
