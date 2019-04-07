#include <iostream>
#include <stdlib.h>
#include <vector>
#include "Posicion.h"
#include "Mapa.h"
#include "Astar.h"

int main()
{
    std::cout << "creando mapa" << std::endl;
    Mapa *m = new Mapa(9,10);
    std::cout << "mapa creado" << std::endl;

    Posicion x = Posicion(0,0);
    Posicion y = Posicion(2,1);
    std::cout << "creando ia" << std::endl;
    Astar *ia = new Astar(x, y, *m);
    std::cout << "ia creada" << std::endl << ";;;;;;;;;;;;;" << std::endl;

    std::cout << "mapeando" << std::endl;
    std::vector<Posicion> path = ia->mapear();
    std::cout << "mapedao hecho" << std::endl;

    std::cout << "Path size: " << path.size() << std::endl;
    for(int a = 0; a < path.size(); a++)
    {
        std::cout << path.at(a).getY() << " .... " << path.at(a).getX() << std::endl;
    }


    delete m;
    exit(0);
}
