#ifndef MAPA_H
#define MAPA_H
//PROVISIONAL

class Mapa
{
    public:
        Mapa(int n, int m);
        virtual ~Mapa();
        int getAltura();
        int getAnchura();
        bool **getMapa();

    protected:

    private:
        bool **m;
        int altura;
        int anchura;
};

#endif // MAPA_H
