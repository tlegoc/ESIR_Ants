#pragma once

#include "Agent.h"

class Pheromone : public Agent
{

public:
    Pheromone(Environment *env, const Vector2<float> &position);
    float getQuantity();
    void addQuantity(float quantity);
    void update();

private:
    float m_quantity = 0.0f;
};