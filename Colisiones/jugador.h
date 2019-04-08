
#include <SFML/Graphics.hpp>
#include <iostream>

class jugador
{

public:
    jugador();
    void movimiento();
    sf::RectangleShape getJugador();
    sf::RectangleShape cuadradoder();
    sf::RectangleShape cuadradoarr();
    sf::RectangleShape cuadradoabaj();
    sf::RectangleShape cuadradoizq();
    void danio(int);
    int getVida();
    sf::Vector2f getPos();
    void setVida();
    void setPosicion(int, int);
    void setPosAnterior();
    void setColision(int);

private:
    sf::RectangleShape *player;
    sf::RectangleShape *cuadrado_der;
    sf::RectangleShape *cuadrado_arr;
    sf::RectangleShape *cuadrado_abj;
    sf::RectangleShape *cuadrado_izq;
    sf::Event *evento;
    int vida;
    int velocidadJugador;
    sf::Vector2f pos_anterior;
    int colisiona;
};
