
#include <SFML/Graphics.hpp>

class enemigo
{
public:
    enemigo();
    sf::RectangleShape getEnemigo();
    void movimiento_enemigo();
    void estado_enemigo();

private:
    sf::RectangleShape *monstruo;
    int vida;
    bool baja = true;

};
