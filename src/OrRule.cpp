#include "OrRule.h"

OrRule::OrRule(std::vector<AbstractRule *> rules)
{
    m_rules = rules;
    m_selected = -1;
}

bool OrRule::condition()
{
    m_selected = -1;
    for (int i = 0; i < m_rules.size(); i++)
    {
        if (m_rules[i]->condition())
        {
            m_selected = i;
            return true;
        }
    }
    return false;
}

void OrRule::action()
{
    if (m_selected != -1)
        m_rules[m_selected]->action();
}

OrRule::~OrRule()
{
    for (auto rule : m_rules)
        delete rule;
}