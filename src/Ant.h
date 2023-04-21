#pragma once

#include "AntBasePheromone.h"

class Ant : public AntBasePheromone
{
public:
    Ant(Environment *env, Anthill *a);
    void update();
};