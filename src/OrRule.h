#pragma once

#include "AbstractRule.h"

#include <vector>

class OrRule : public AbstractRule
{
public:
    OrRule(std::vector<AbstractRule> rules);
    bool condition();
    void action();

private:
    std::vector<AbstractRule> m_rules;
    int m_selected;
};