
#include <SFML/Graphics.hpp>
#include <vector>

class hud
{
public:
    hud();
    ~hud();
    sf::Text getTextoVida();
    std::vector<sf::Sprite> getArrayVida();
    std::vector<sf::Sprite> getArrayHabilidades();
    sf::Sprite getCorazon();
    void setPosicionCorazones();
    void setPosicionHabilidades();
    void modificar_vida(int,int);
    void setHabilidad(int);
    int getCantidadVida();
    int getCantidadHabilidades();
    sf::RectangleShape getPiezaVida();
    sf::RectangleShape getPiezaHabilidades();

private:
    sf::Text *texto_vida;
    sf::Font *fuente;
    sf::RectangleShape * pieza_vida;
    sf::RectangleShape * pieza_habilidades;

    sf::Texture *textura_vida;
    sf::Sprite *corazon;
    sf::Texture *textura_habilidades;
    sf::Sprite *mejora_escudo;
    sf::Sprite *mejora_ataque;
    sf::Sprite *rompe_escudos;
    sf::Sprite *mana;
    sf::Sprite *mejora_cofre;
    sf::Sprite *espada_magica;

    std::vector<sf::Sprite> *cantidad_corazones;
    std::vector<sf::Sprite> *vector_habilidades;
};
