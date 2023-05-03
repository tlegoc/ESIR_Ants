#include "AntWithRules.h"

#include "OrRule.h"

AntWithRules::AntWithRules(Environment *env, Anthill *a) : AntBasePheromone(env, a)
{
    m_rule = OrRule({});
}

AntWithRules::AntWithRules(Environment *env, Anthill *a, std::vector<AbstractRule> rules) : AntBasePheromone(env, a)
{
    m_rule = OrRule(rules);
}

void AntWithRules::update()
{
    if (m_rule.condition())
        m_rule.action();

    updateLifetime();
    render();
};

void AntWithRules::setRule(OrRule rule)
{
    m_rule = rule;
}