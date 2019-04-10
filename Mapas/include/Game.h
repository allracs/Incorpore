#include <SFML/Graphics.hpp>
#include <iostream>
#include "Player.h"
#include "Hud.h"
#include "Mapa.h"

using namespace sf;

class game
{
    public:
        game();
        void gameLoop();
        void render();
        void cargaPlayer();
        void cargaMapa();
        void cargarHUD();
        void procesarEventos();
        void setView();
        void mostrarMapaColisiones();
        void procesarColisiones();
        void setColisions();
        View getView();

        int* dimensiones;
    private:
        RenderWindow *window;
        Player *jugador;
        Event *evento;
        Mapa *mapa;
        Hud *hud_principal;
        View view;
        FloatRect* colisiones;

};
