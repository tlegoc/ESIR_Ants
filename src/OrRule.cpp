#include "OrRule.h"

#include <iostream>

OrRule::OrRule(AbstractRule *rule1, AbstractRule *rule2)
{
    m_rule1 = rule1;
    m_rule2 = rule2;
}

bool OrRule::condition()
{
    return m_rule1->condition() || m_rule2->condition();
}

void OrRule::action()
{
    if (m_rule1->condition())
        m_rule1->action();
    if (m_rule2->condition())
        m_rule2->action();
}

OrRule::~OrRule()
{
    delete m_rule1;
    delete m_rule2;
}