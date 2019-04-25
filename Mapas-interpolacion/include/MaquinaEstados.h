#ifndef MAQUINAESTADOS_H
#define MAQUINAESTADOS_H

#include <SFML/Graphics.hpp>
#include<memory>
#include<stack>
#include<string>

class Estado;

class MaquinaEstados
{
    public:
        MaquinaEstados();
        virtual ~MaquinaEstados();

        void run(std::unique_ptr<Estado> estado);

        void siguienteEstado();
        void ultimoEstado();
        void update();
        void draw();

        bool corriendo() {return m_corriendo;}
        void quit(){m_corriendo = false;}

        template <typename T>
        static std::unique_ptr<T> build(MaquinaEstados& maquina, sf::RenderWindow& window, bool cambio = true);

    protected:

    private:

        std::stack<std::unique_ptr<Estado>> m_estados;

        bool m_resume;
        bool m_corriendo;
};

        template <typename T>
        std::unique_ptr<T> MaquinaEstados::build(MaquinaEstados& maquina, sf::RenderWindow& window, bool cambio)
        {
            return std::unique_ptr<T>(new T(maquina, window, cambio));
        }


#endif // MAQUINAESTADOS_H
