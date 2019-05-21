#include "../include/Estado.h"

Estado::Estado(MaquinaEstados& maquina, sf::RenderWindow& window, bool cambio): m_maquina {maquina}, m_window {window}, m_replacing {cambio}
{

}

Estado::~Estado()
{
    //dtor
}

std::unique_ptr<Estado> Estado::siguiente()
{
    return std::move(m_siguiente);
}

bool Estado::isReplacing()
{
    return m_replacing;
}
