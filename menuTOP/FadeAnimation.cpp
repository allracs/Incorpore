
#include "FadeAnimation.h"

FadeAnimation::FadeAnimation(void)
{

}


FadeAnimation::~FadeAnimation(void)
{

}

void FadeAnimation::LoadContent(std::string text, sf::Texture image, sf::Vector2f position)
{
    //Animation animation;
    //Animation prueba;
    //animation.LoadContent(text,image,position);
    Animation::LoadContent(text,image,position);
    // ::LoadContent(text,image,position);

    increase = false;
    fadeSpeed= 1.0f;
}

void FadeAnimation::UnloadContent()
{

}
void FadeAnimation::Update(sf::RenderWindow &Window)
{
sf::Clock Clock;
    if(active)
    {
        if(!increase)

        alpha-= Clock.getElapsedTime().asSeconds()*fadeSpeed;
        // Window.get getFrame; reset clock ?
        else
        alpha +=Clock.getElapsedTime().asSeconds()*fadeSpeed;
        //sf::Clock

        if(alpha>=1.0f)
        {
            alpha=1.0f;
            increase=false;
        }
        else if(alpha<=0.0f)
        {
        alpha = 0.0f;
        increase = true;
        }
    }
    else
    {
    alpha = 1.0f;
    }
}

void FadeAnimation::Draw(sf::RenderWindow &Window)
{
    Animation::Draw(Window);
}

void FadeAnimation::SetAlpha(float value)
{
    alpha = value;

    if(alpha ==0.0f)
        increase=true;
    else
        increase=false;
}
