#ifndef ENEMIGO_H
#define ENEMIGO_H


class Enemigo
{
    public:
        Enemigo();
        virtual ~Enemigo();
        void serAtacado(Jugador j);

    private:
        sf::RectangleShape enemigoHitbox;

};

#endif // ENEMIGO_H
