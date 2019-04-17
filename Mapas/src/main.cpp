#include <iostream>
#include <SFML/Graphics.hpp>
#include "../include/Aplicacion.h"

using namespace std;

int main(int argc, char *argv[]){

    //Juego *partida = Juego::Instance();

    Aplicacion aplicacion;
    aplicacion.run();

    return 0;
}
