#include <SFML/Graphics.hpp>
#include <iostream>
#include "Jugador.h"
#include "Enemigo.h"
#include "Hud.h"
#include "Mapa.h"

using namespace sf;

class Juego
{
    public:
        static Juego* Instance();
        Juego();
        void cargaPlayer();
        void cargaMapa();
        void cargarHUD();
        void gameLoop();

        void procesarEventos();
        void setView();
        void render();

        Vector2i dimensiones;
    private:
        static Juego* pinstance;

        RenderWindow *window;
        RenderStates *states;
        Clock frameClock;
        Jugador *jugador;
        Enemigo **enemigos;
        Event *evento;
        Mapa *mapa;
        Hud *hud;
        View view;

        bool centrado;
        float delta;
        int nEnemigos;
};
