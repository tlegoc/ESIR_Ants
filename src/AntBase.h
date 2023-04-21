#pragma once

#include "Agent.h"

#include "Anthill.h"
#include "Food.h"

class AntBase : public Agent
{
public:
    AntBase(Environment *env, Anthill *anthill);

    void setTarget(const Vector2<float> &target);
    void setTarget(const Agent * a);

    void render();

    void turn(const float angle,const bool clockwise = true);
    void turnAround();

    /// @brief Drops food to the nearest and most usefull food container
    /// first it checks for anthills, then food packs, and if there's none it creates 
    /// a food pack and drop all the food to it.
    void dropFood();
    void dropFood(Anthill *hill);
    void dropFood(Food *hill);

    void updateLifetime();

protected:
    float m_current_food = 0.0f;

    Vector2<float> m_direction;
    float m_speed = 1.0f;

    float m_viewing_angle = MathUtils::piDiv2;
    float m_viewing_distance = 3.0f;

    Anthill * m_anthill;

    const float m_lifetime;
    float m_life_elapsed = 0.0f;
};