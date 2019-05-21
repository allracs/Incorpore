#ifndef ESTADO_H
#define ESTADO_H

#include <SFML/Graphics.hpp>
#include<memory>

class MaquinaEstados;

class Estado
{
    public:
        Estado(MaquinaEstados& maquina, sf::RenderWindow& window, bool cambio = true);
        virtual ~Estado();

        Estado(const Estado&) = delete;

        Estado& operator=(const Estado&) = delete;

        virtual void pause() = 0;
        virtual void resume() = 0;
        virtual void update() = 0;
        virtual void draw() = 0;

        std::unique_ptr<Estado> siguiente();

        bool isReplacing();

    protected:
        MaquinaEstados& m_maquina;
        sf::RenderWindow& m_window;
        bool m_replacing;
        std::unique_ptr<Estado> m_siguiente;

    private:
};

#endif // ESTADO_H
