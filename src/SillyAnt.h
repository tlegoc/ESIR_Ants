#pragma once

#include "AntBase.h"

class SillyAnt : public AntBase
{
public:
    SillyAnt(Environment *env, Anthill *a);
    void update();
};