#include "AntWithRules.h"

#include "OrRule.h"

AntWithRules::AntWithRules(Environment *env, Anthill *a, AbstractRule *rule1, AbstractRule *rule2) : AntWithRules(env, a, new OrRule(rule1, rule2))
{
}

AntWithRules::AntWithRules(Environment *env, Anthill *a, AbstractRule *rule) : AntBasePheromone(env, a)
{
    m_rule = rule;
}

void AntWithRules::update()
{
    if (m_rule->condition())
        m_rule->action();

    updateLifetime();
    render();
};

void AntWithRules::setRule(OrRule *rule)
{
    m_rule = rule;
}

AntWithRules::~AntWithRules()
{
    delete m_rule;
}