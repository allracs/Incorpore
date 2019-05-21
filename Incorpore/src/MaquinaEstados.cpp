#include "../include/MaquinaEstados.h"
#include "../include/Estado.h"
#include <iostream>
#include <memory>


MaquinaEstados::MaquinaEstados(): m_resume {false}, m_corriendo {false}
{
//    std::cout << "Maquina de estados iniciada" << std::endl;
}

MaquinaEstados::~MaquinaEstados()
{
    //dtor
}

void MaquinaEstados::run(std::unique_ptr<Estado> estado)
{
    m_corriendo = true;
    m_estados.push(std::move(estado));
}

void MaquinaEstados::siguienteEstado()
{
    if(m_resume)
    {
        if(!m_estados.empty())
        {
            m_estados.pop();//quitamos la cabeza
            m_estados.top()->resume();//se ejecuta la cabeza actual
        }

        m_resume = false;
    }

    if(!m_estados.empty())
    {
        std::unique_ptr<Estado> temporal = m_estados.top()->siguiente();

        if(temporal != nullptr)// comprueba si hay un siguiente estado
        {
            if(temporal->isReplacing()) // si se va a reemplazar el estado, quitamos la cabeza de la pila
            {
                m_estados.pop();
            }
            else
            {
                m_estados.top()->pause(); //pause la cabeza de la pila
            }

            m_estados.push(std::move(temporal));// ponemos en la cabeza el estado temporal
        }
    }
}


void MaquinaEstados::ultimoEstado()
{
    m_resume = true;
}

void MaquinaEstados::update()
{
    m_estados.top()->update();
}

void MaquinaEstados::draw()
{
    m_estados.top()->draw();
}




