
#include <SFML/Graphics.hpp>
#include <iostream>

class jugador
{

public:
    jugador();
    void move_der();
    void move_izq();
    void move__abaj();
    void move__arr();
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
