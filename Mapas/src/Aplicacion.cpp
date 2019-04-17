#include "Aplicacion.h"



Aplicacion::Aplicacion()
{
    //ctor
}

Aplicacion::~Aplicacion()
{
    //dtor
}

void Aplicacion::run()
{
    m_window.create(sf::VideoMode(1280,720), "Incorpore");
    m_window.setFramerateLimit(30);

    m_maquina.run(MaquinaEstados::build<Menu>(m_maquina, m_window, true));

    while(m_maquina.corriendo())
    {
        m_maquina.siguienteEstado();
        m_maquina.update();
        m_maquina.draw();
    }
}
