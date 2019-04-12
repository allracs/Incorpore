

#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>



class menu
{
public:
    menu();

    ///getters
    sf::Sprite getFondo();
    sf::Sprite getFondOpciones();
    std::vector<sf::Text> getOpciones();
    int opcion_seleccionada();
    sf::Text getTitulo();

    ///setters
    void setPosicion(int, int);
    void setOpcionMenu(int);
    void setColorOp();


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
};
