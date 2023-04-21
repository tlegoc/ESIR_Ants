#include "Ant.h"

#include "Timer.h"

Ant::Ant(Environment *env, Anthill *a) : AntBasePheromone(env, a)
{
}

void Ant::update()
{
    if (m_current_food > 0)
    {
        std::vector<Anthill *> anthills = LocalizedEntity::perceive<Anthill>();

        if (!anthills.empty() && std::find(anthills.begin(), anthills.end(), m_anthill) != anthills.end())
        {
            dropFood(m_anthill);
            turnAround();
        }
        else
        {
            setTarget(m_anthill);
            Pheromone *p = choosePheromone();
            if (p != nullptr)
            {
                setTarget(p);
            }
        }

        putPheromone(100);
    }
    else
    {
        std::vector<Food *> food_touching = LocalizedEntity::perceive<Food>();
        std::vector<Food *> food_close = LocalizedEntity::perceive<Food>(m_direction, m_viewing_angle, m_viewing_distance);

        if (!food_touching.empty())
        {
            m_current_food += food_touching.back()->collectFood(5 - m_current_food);
        }
        else if (!food_close.empty())
        {
            setTarget(food_close.back());
        }
        else if (Pheromone *p = choosePheromone())
        {
            setTarget(p);
        }
        else
        {
            float turn_angle = MathUtils::random(-MathUtils::pi / 10 * Timer::dt(), MathUtils::pi / 10 * Timer::dt());

            turn(turn_angle);
        }

        putPheromone(10);
    }

    translate(m_direction * m_speed * Timer::dt());
    updateLifetime();
    render();
}