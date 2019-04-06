#ifndef POSICION_H
#define POSICION_H


class Posicion
{
    public:
        Posicion(int n, int m, Posicion p);
        virtual ~Posicion();
        void setG(Posicion p, int valor);
        void setH(Posicion i, Posicion f);
        void setH(int n);

        int getG();
        int getH();
        int getF();

        int getX();
        int getY();
        Posicion getPadre();

    protected:

    private:
        int x, y, *g, *h;
        bool pared;
        Posicion *padre;
};

#endif // POSICION_H
