#pragma once

#include "Agent.h"
#include "Environment.h"

class Food : public Agent
{
public:
    Food(Environment * env, const Vector2<float> &position, float quantity);

    float getFoodQuantity() const;
    float collectFood(float quantity);
    void addFood(float quantity);

    void update();

private:
    const float m_max_food;
    float m_current_food;
};