#pragma once

#include "AntBase.h"

#include "Pheromone.h"

class AntBasePheromone : public AntBase
{
public:
    void putPheromone(float quantity);
    Pheromone *choosePheromone();
};