#include <iostream>
#include <stdlib.h>
#include <vector>
#include "Posicion.h"
#include "Mapa.h"
#include "Astar.h"

int main()
{

                        //Y,X
    Posicion x = Posicion(1,1);
    Posicion y = Posicion(8,7);
    std::cout << "creando ia" << std::endl;
    int alt = 9;
    int anc = 10;
    bool j[alt][anc] =
	{  // 0  1  2  3  4  5  6  7  8  9
		{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 }, // 0
		{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 1 }, // 1
		{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 1 }, // 2
		{ 1, 1, 1, 0, 0, 0, 0, 0, 0, 1 }, // 3
		{ 1, 1, 0, 0, 1, 1, 1, 0, 1, 1 }, // 4
		{ 1, 0, 0, 1, 1, 1, 0, 1, 0, 1 }, // 5
		{ 1, 0, 0, 0, 0, 1, 0, 0, 0, 1 }, // 6
		{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 1 }, // 7
		{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 }  // 8
	};

	bool **jj = new bool *[alt];
	for(int a = 0; a < alt; a++){
        jj[a] = new bool[anc];
	}

    for(int a = 0; a < alt; a++)
    {
        for(int b = 0; b < anc; b++)
        {
            jj[a][b] = j[a][b];
        }
    }

    Astar *ia = new Astar(x, y, jj, alt, anc);
    std::cout << "ia creada" << std::endl << ";;;;;;;;;;;;;" << std::endl;

    std::cout << "mapeando" << std::endl;
    std::vector<Posicion> path = ia->mapear();
    std::cout << "mapedao hecho" << std::endl;

    std::cout << "Path size: " << path.size() << std::endl;
    for(int a = 0; a < path.size(); a++)
    {
        std::cout << path.at(a).getY() << " .... " << path.at(a).getX() << std::endl;
    }

    std::cout << "________EL CAMINO________" << std::endl << std::endl;

    if(path.size()==0){
        std::cout << " ------- No hay solucion posible -------" << std::endl;
        std::cout << " ------- Feels Bad Man D: -------" << std::endl;
    }
    else
    {
        int flag = true;
        for(int a = 0; a < alt; a++)
        {
            std::cout << "  ";
            for(int b = 0; b < anc; b++)
            {
                flag = true;
                for(int c = 0; c < path.size()-1; c++)
                {
                    if(path.at(c).getX() == b && path.at(c).getY() == a)
                    {
                        std::cout << "- ";
                        flag = false;
                        break;
                    }
                }
                if(flag && x.getY()== a && x.getX() == b)
                {
                    std::cout << "# ";
                    flag = false;
                }
                if(flag && y.getY()== a && y.getX() == b)
                {
                    std::cout << "@ ";
                    flag = false;
                }
                if(flag)
                {
                    if(jj[a][b] == 1)
                    {
                        std::cout << "1 ";
                    }
                    else
                    {
                        std::cout << "0 ";
                    }
                }
            }
            std::cout << std::endl << std::endl;
        }

    }


    exit(0);
}
