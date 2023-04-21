#pragma once

#include "AntBase.h"

#include "Pheromone.h"

class AntBasePheromone : public AntBase
{
public:
    AntBasePheromone(Environment *env, Anthill *a);
    void putPheromone(float quantity);
    Pheromone *choosePheromone();
};