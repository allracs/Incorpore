#ifndef APLICACION_H
#define APLICACION_H

#include "MaquinaEstados.h"
#include "Menu.h"

#include <SFML/Graphics.hpp>

class Aplicacion
{
    public:
        Aplicacion();
        virtual ~Aplicacion();

        void run();

    protected:

    private:

        MaquinaEstados m_maquina;
        sf::RenderWindow m_window;
};

#endif // APLICACION_H
