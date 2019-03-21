#include <SFML/Graphics.hpp>
using namespace sf;
using namespace std;

class player{
    public:
        player();
        void movimiento();
        RectangleShape getPlayer();
    private:
        RectangleShape *jugador;
        int velocidad;
};
