#ifndef MENU_H
#define MENU_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Estado.h"

class MaquinaEstados;


class Menu : public Estado
{
    public:
        Menu(MaquinaEstados& maquina, sf::RenderWindow& window, bool cambio = true);
        virtual ~Menu();

        void pause();
        void resume();
        void update();
        void draw();

        ///setters
        void setPosicion(int, int);
        void setOpcionMenu(int);
        void setColorOp();


        void procesar_eventos();
        void eventos_raton();

        void cambio();
        void recortes(int);

    protected:

    private:
        std::vector<sf::Text> *botones;
        void eventos();
        sf::Font *fuente;
        sf::Font *titulofuente;
        sf::Text *titulo;
        sf::Text *jugar;
        sf::Text *opciones;
        sf::Text *salir;
        int seleccion = 0;
        sf::Texture *texfondo;
        sf::Sprite *sprfondo;
        sf::Texture *texopciones;
        sf::Sprite *spropciones;
        sf::RenderWindow *window;

        sf::Music musica;

        sf::Event *evento;
        sf::Mouse *raton;
        bool menuprincipal = true;
        bool sel_raton = false;
        bool sel_teclado = true;
        int opcion_seleccionada = 0;
        sf::Clock clkmenu;
        int num = 1;
        int linea = 1;
    };

#endif // MENU_H
