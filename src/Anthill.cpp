#include "Anthill.h"

#include "Renderer.h"
#include "SillyAnt.h"

Anthill::Anthill(Environment *env, const Vector2<float> &position) : Agent(env, position, 10)
{
}

void Anthill::depositFood(float quantity)
{
    m_current_food += quantity;
}

void Anthill::update()
{
    Renderer::getInstance()->drawCircle(getPosition(), getRadius(), Renderer::Color(0, 0, 255, 255));
}
