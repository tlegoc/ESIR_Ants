#include "AntBase.h"

#include "MathUtils.h"
#include "Renderer.h"
#include "Food.h"
#include "Timer.h"

AntBase::AntBase(Environment *env, Anthill *anthill) : Agent(env, anthill->getPosition(), 1),
                                                       m_lifetime(MathUtils::random(1000, 2500))
{
    m_anthill = anthill;
    m_direction = Vector2<float>(1.0f, 0.0f);
}

void AntBase::setTarget(const Vector2<float> &target)
{
    m_direction = (target - getPosition()).normalized();
}

void AntBase::setTarget(const Agent *a)
{
    setTarget(a->getPosition());
}

void AntBase::turn(const float angle, const bool clockwise)
{
    m_direction = m_direction.rotate((clockwise ? 1.0f : -1.0f) * angle);
}

void AntBase::turnAround()
{
    turn(MathUtils::pi);
}

void AntBase::dropFood()
{
    std::vector<Anthill *> anthills = LocalizedEntity::perceive<Anthill>();

    if (!anthills.empty())
    {
        dropFood(anthills.back());
        return;
    }

    std::vector<Food *> foods = LocalizedEntity::perceive<Food>();

    if (!foods.empty())
    {
        dropFood(foods.back());
        return;
    }

    Food *f = new Food(getEnvironment(), getPosition(), m_current_food);
    m_current_food = 0;
}

void AntBase::dropFood(Anthill *a)
{
    a->depositFood(m_current_food);
    m_current_food = 0;
}

void AntBase::dropFood(Food *a)
{
    a->addFood(m_current_food);
    m_current_food = 0;
}

void AntBase::render()
{
    Renderer::getInstance()->drawPixel(getPosition(), m_current_food > 0 ? Renderer::Color(128, 255, 128) : Renderer::Color(255, 255, 255));
}

void AntBase::updateLifetime() {
    m_life_elapsed += Timer::dt();

    if (m_life_elapsed > m_lifetime) 
        setStatus(Status::destroy);
}