
#include <SFML/Graphics.hpp>
#include <iostream>
#include "jugador.h"
#include "enemigo.h"
#include "mapa.h"
#include "objetos.h"
#include "hud.h"

class juego
{
public:
    juego();
    void game_loop();
    void render();
    void cargador_mapa();
    void cargador_jugador();
    void cargador_enemigo();
    void cargador_objetos();
    void procesar_eventos();
    void procesar_colisiones();
    void movimiento_enemigo();
    void mostrar_vida();
    void cargar_hud();

private:
    sf::RenderWindow *window;

    mapa *pared_superior;
    mapa *pared_inferior;
    mapa *pared_derecha;
    mapa *pared_izquierda;
    mapa *columna;

    jugador *personaje;
    enemigo *monstruo;
    objetos *pocion;
    hud *vida_personaje;
    hud *vida_enemigo;

    bool borrado = false;

    bool izquierda = true;
    bool derecha = true;
    bool arriba = true;
    bool abajo = true;

    sf::Event *evento;
};
