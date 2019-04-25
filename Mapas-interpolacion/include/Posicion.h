#ifndef POSICION_H
#define POSICION_H

class Posicion
{
    public:
        Posicion(int n, int m, Posicion p);
        Posicion(int n, int m);
        virtual ~Posicion();
        void setG(Posicion p, int valor);
        void setH(Posicion i, Posicion f);
        void setH(int n);
        void copyGH(int gg, int hh);

        int getG();
        int getH();
        int getF();

        int getX();
        int getY();
        Posicion getPadre();

    protected:

    private:
        int x, y;
        int g, h;
        bool pared;
        Posicion *padre;
};

#endif // POSICION_H
