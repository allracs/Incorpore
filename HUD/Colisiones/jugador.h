
#include <SFML/Graphics.hpp>

class jugador
{

public:
    jugador();
    void movimiento(int);
    sf::RectangleShape getJugador();
    void danio(int);
    int getVida();
    sf::Vector2f getPos();
    void setVida();
    void setPosicion(int, int);

private:
    sf::RectangleShape *player;
    sf::Event *evento;
    int vida;
    int velocidadJugador;
};
