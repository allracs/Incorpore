
#include <SFML/Graphics.hpp>

class objetos
{
public:
    objetos();
    sf::RectangleShape getObjeto();
    ~objetos();
    bool dibujado;

private:
    sf::RectangleShape *objeto;
};
