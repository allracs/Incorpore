#include "JuegoState.h"

//includeeeeeeeeeeeeeeeeesss
//ojo los parametros corregir
JuegoState::JuegoState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states)
: State(window, states)//remember he quitado el segundo parametro q era suportedkeys
{
    nEnemigos = 1;//A GAMESTATE --- DE JUEGO
   // this->initKeybinds(); useless
    view.setSize(dimensiones.x, dimensiones.y);// esto seria de game state,
    view.zoom(0.2f);//game state -- de juego

    centrado = false;//game state -- de juego

    cargaPlayer();//game state -- de juego
    cargaMapa();//game state -- de juego
    cargarHUD();//game state -- de juego
    gameLoop();//game state -- de juego
}


void JuegoState::render(sf::RenderTarget* target)
{
        if(!target)
            target = this->window;

            //ESTO DEBERIA ESTAR EN CADA ENTIDAD QUE LE TOCA NO AQUI APELOTONADO
            mapa->draw(*window, *jugador, *enemigos, nEnemigos);//PASAR A GAMESTATE DONE
            hud->draw(*window);//GAMESTATE
            jugador->drawBoundingBoxes(*window);//PASAR A GAMESTATE

            //aqui iria el render de mapa
            this->player.render(target);
             enemigos[0]->drawBoundingBoxes(*window);//PASAR A GAMESTATE
}




void Juego::cargarHUD(){//A GAME STATE --- PASADO DE JUEGO
    hud = new Hud();
    hud->setPosicionVida(view.getCenter().x - dimensiones.x/10 + 4, view.getCenter().y - dimensiones.y/10);
    hud->setPosicionHabilidades(view.getCenter().x - hud->getPiezaHabilidades().getGlobalBounds().width/2, view.getCenter().y + dimensiones.y/10 - hud->getPiezaHabilidades().getGlobalBounds().height);
}

void Juego::cargaMapa(){//A GAME STATE --- PASADO DE JUEGO
    mapa = new Mapa;
}

//sustituye a mi rectangle shape con move - A GAME STATE
void Juego::cargaPlayer(){
    jugador = new Jugador({150, 50});
    enemigos = new Enemigo*[nEnemigos];
    for(int i = 0; i < nEnemigos; i++){
        enemigos[i] = new Enemigo({150, 100*(i+1)});
    }
    view.setCenter(jugador->getActual()->sprite.getPosition().x, jugador->getActual()->sprite.getPosition().y);
}

Juego* Juego::pinstance = 0;//A GAMESTATE

Juego* Juego::Instance(){//EL MAIN LLAMA A ESTO PARA EMPEZAR LA PARTIDA
    if(pinstance == 0)
        pinstance = new Juego;
    return pinstance;
}

void JuegoState::setView(){
    view.move(jugador->getMovement() * delta);
    hud->move(jugador->getMovement() * delta);
}


void Juego::manejarIA(){ // PASADO DE JUEGO

    if(true){   // anyadir clock para que se ejecute cada X tiempo

        Vector2i v = mapa->getPosicionEntidad(*jugador);
        Posicion pos_jugador = Posicion(v.x, v.y);

        // para cada enemigo crear Posicion y llamar a la IA
        // nEnemigos: numero de enemigos en el mapa

        for(int a = 0; a < nEnemigos; a++){

            Vector2i e = mapa->getPosicionEntidad(*enemigos[a]);
            Posicion pos_enemigo = Posicion(e.x, e.y);
            //asignar posicion al enemigo
            //se crea el astar
            Astar ia = Astar(pos_jugador, pos_enemigo, mapa->getColisiones(), mapa->getHeight(), mapa->getWidth());

            //se llama a astar.mapear()
            std::vector<Posicion> path = ia.mapear();
            std::cout << path.size() << std::endl;

            enemigos[a]->setPath(path);

            // SEGUIR EL CAMINO (CON BUCLE INTERPOLADO)
            // mover a enemigos[a] hacia el siguiente punto

            int flag = true;
            for(int a = 0; a < mapa->getHeight(); a++)
            {
                std::cout << "  ";
                for(int b = 0; b < mapa->getWidth(); b++)
                {
                    flag = true;
                    for(int c = 0; c < path.size()-1; c++)
                    {
                        if(path.at(c).getX() == b && path.at(c).getY() == a)
                        {
                            std::cout << "-";
                            flag = false;
                            break;
                        }
                    }
                    if(flag && v.x == b && v.y == a)
                    {
                        std::cout << "#";
                        flag = false;
                    }
                    if(flag && e.x == b && e.y == a)
                    {
                        std::cout << "@";
                        flag = false;
                    }
                    if(flag)
                    {
                        if(mapa->getColisiones()[a][b] == 1)
                        {
                            std::cout << "1";
                        }
                        else
                        {
                            std::cout << "0";
                        }
                    }
                }
                std::cout << std::endl;
            }

        } //fin for each enemigo
    }
}

//SEGURAMENTE USELESS, LO DEJO DE MOMENTO POR SI ACA
 void JuegoState::updateInput(const float & dt)
 {
 this->checkForQuit();
 //codigo de los controles useless
  }


JuegoState::~JuegoState(){}

void JuegoState::endState()
{
std::cout <<"Se acaba el juego" <<"\n";
}
