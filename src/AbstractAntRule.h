#pragma once

#include "AbstractRule.h"
#include "AntBase.h"

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