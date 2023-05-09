#pragma once

#include "AbstractRule.h"

#include <vector>

class OrRule : public AbstractRule
{
public:
    OrRule() = delete;
    OrRule(AbstractRule *rule1, AbstractRule *rule2);
    bool condition();
    void action();
    ~OrRule();

private:
    AbstractRule *m_rule1;
    AbstractRule *m_rule2;
};