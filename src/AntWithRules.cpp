#include "AntWithRules.h"

#include "OrRule.h"

AntWithRules::AntWithRules(Environment *env, Anthill *a) : AntBasePheromone(env, a)
{
    m_rule = new OrRule({});
}

AntWithRules::AntWithRules(Environment *env, Anthill *a, std::vector<AbstractRule *> rules) : AntBasePheromone(env, a)
{
    m_rule = new OrRule(rules);
}

void AntWithRules::update()
{
    if (m_rule->condition())
        m_rule->action();

    updateLifetime();
    render();
};

AntWithRules::~AntWithRules()
{
    delete m_rule;
}

void AntWithRules::setRule(AbstractRule *rule)
{
    delete m_rule;
    m_rule = rule;
}