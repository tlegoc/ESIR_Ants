#pragma once

#include "Agent.h"
#include "Environment.h"

class Anthill : public Agent
{
public:
    Anthill(Environment *env, const Vector2<float> &position);
    void depositFood(float quantity);
    void update();

private:
    float m_current_food;
};