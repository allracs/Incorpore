#pragma once
#ifndef ANIMATION_H
#define ANIMATION_H
#include<SFML/Graphics.hpp>
#include<string>

class Animation
{
    public:
        Animation(void);
        ~Animation(void);

       virtual void LoadContent(std::string text, sf::Texture image, sf::Vector2f position);
       virtual void UnloadContent();
       virtual void Update(sf::RenderWindow &Window);
       virtual void Draw(sf::RenderWindow &Window);


        virtual void SetAlpha(float alpha);
        float GetAlpha();

        void SetActive(bool value);

    protected:
            float alpha;
            sf::Text text;
            std::string preText;
            //std::string pretext

            //el tiene string
            //esto va a ser Text
            sf::Texture image;
            //sf::Sprite image;
            sf::Sprite sprite;
            sf::Vector2f position;
            sf::Color textColor;

            sf::IntRect sourceRect;
            bool active;

    private:
};

#endif // ANIMATION_H
