#pragma once
#include "Animation.h"

class FadeAnimation : public Animation
{
public:
    FadeAnimation(void);
    ~FadeAnimation(void);

    void LoadContent(std::string text, sf::Texture image, sf::Vector2f position);
    void UnloadContent();
    void Update(sf::RenderWindow &Window);
    //clock
    void Draw(sf::RenderWindow &Window);
    void SetAlpha(float value);

private:
    bool increase;
    float fadeSpeed;
    int startAlpha;
    int endAlpha;

};
