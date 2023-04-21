#include "SillyAnt.h"

#include "Timer.h"
#include "Food.h"
#include <iostream>

SillyAnt::SillyAnt(Environment *env, Anthill *a) : AntBase(env, a)
{
    m_direction = Vector2<float>::random().normalized();
}

void SillyAnt::update()
{
    if (m_current_food > 0)
    {
        setTarget(m_anthill);
        translate(m_direction * m_speed * Timer::dt());

        std::vector<Anthill *> anthills = LocalizedEntity::perceive<Anthill>();

        if (!anthills.empty())
        {
            dropFood(anthills.back());
        }

        turnAround();
    }
    else
    {
        float turn_angle = MathUtils::random(-MathUtils::pi / 10 * Timer::dt(), MathUtils::pi / 10 * Timer::dt());

        turn(turn_angle);
        translate(m_direction * m_speed * Timer::dt());

        std::vector<Food *> foods = LocalizedEntity::perceive<Food>();

        if (!foods.empty()) {
            m_current_food += foods.back()->collectFood(5 - m_current_food);
        }
    }

    updateLifetime();

    render();
}