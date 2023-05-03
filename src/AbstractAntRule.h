#pragma once

#include "AbstractRule.h"
#include "AntBase.h"

#include <iostream>

class AbstractAntRule : public AbstractRule
{
public:
    AbstractAntRule(AntBase *ant)
    {
        m_ant = ant;
    }

protected:
    AntBase *m_ant;
};