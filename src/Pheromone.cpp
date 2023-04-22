#include "Pheromone.h"

#include "Timer.h"
#include "Renderer.h"

Pheromone::Pheromone(Environment *env, const Vector2<float> &position) : Agent(env, position, defaultRadius())
{
}

void Pheromone::addQuantity(float quantity)
{
    m_quantity += quantity;
}

float Pheromone::getQuantity()
{
    return m_quantity;
}

void Pheromone::update()
{
    m_quantity -= m_quantity * 0.01f * Timer::dt();
    if (m_quantity <= 0.01)
    {
        setStatus(Status::destroy);
        return;
    }

    Renderer::getInstance()->drawPixel(getPosition(), Renderer::Color(0, 128, 128, std::min(255.0f, m_quantity)));
}