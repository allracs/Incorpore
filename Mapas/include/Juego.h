#include <SFML/Graphics.hpp>
#include <iostream>
#include "Jugador.h"
#include "Hud.h"
#include "Mapa.h"

using namespace sf;

class Juego{
    public:
        Juego();
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
        RenderStates *states;
        Jugador *jugador;
        Event *evento;
        Mapa *mapa;
        Hud *hud_principal;
        View view;
};
