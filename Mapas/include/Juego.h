#include <SFML/Graphics.hpp>
#include <iostream>
#include "Jugador.h"
#include "Hud.h"
#include "Mapa.h"

using namespace sf;

class Juego{
    public:
        Juego();
        void cargaMapa();
        void cargarHUD();
        void cargaPlayer();
        void gameLoop();

        void procesarEventos();
        void setView();
        void render();

        int* dimensiones;
    private:
        RenderWindow *window;
        RenderStates *states;
        Jugador *jugador;
        Event *evento;
        Mapa *mapa;
        Hud *hud;
        View view;
};
