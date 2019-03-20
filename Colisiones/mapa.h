
#include <SFML/Graphics.hpp>

class mapa
{

public:
    mapa();
    sf::RectangleShape getParedSuperior();
    sf::RectangleShape getParedInferior();
    sf::RectangleShape getParedDerecha();
    sf::RectangleShape getParedIzquierda();
    sf::RectangleShape getColumna();

private:
    sf::RectangleShape *pared_superior;
    sf::RectangleShape *pared_inferior;
    sf::RectangleShape *pared_derecha;
    sf::RectangleShape *pared_izquierda;
    sf::RectangleShape *columna;
    int pid;

};
