#include <SFML/Graphics.hpp>
using namespace sf;
using namespace std;

class player{
    public:
        player();
        void movimiento();

        RectangleShape getJugador();
        RectangleShape cuadradoder();
        RectangleShape cuadradoarr();
        RectangleShape cuadradoabaj();
        RectangleShape cuadradoizq();

        RectangleShape getPlayer();

        void setColision(int);
        void setPosicion(int, int);
    private:
        RectangleShape *jugador;
        int velocidad;
        RectangleShape *cuadrado_der;
        RectangleShape *cuadrado_arr;
        RectangleShape *cuadrado_abj;
        RectangleShape *cuadrado_izq;
        int colisiona;
};
