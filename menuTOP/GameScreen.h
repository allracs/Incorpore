#ifndef GAMESCREEN_H
#define GAMESCREEN_H
#include<SFML/Graphics.hpp>


class GameScreen
{
    public:
            GameScreen();
            ~GameScreen();

            virtual void LoadContent();
            virtual void UnloadContent();
            virtual void Update();
            virtual void Draw(sf::RenderWindow &Window);
    protected:
    private:

};
#endif // gamescreen_h
