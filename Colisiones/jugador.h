
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
    void setPosAnterior();

private:
    sf::RectangleShape *player;
    sf::Event *evento;
    int vida;
    int velocidadJugador;
    sf::Vector2f pos_anterior;
};
