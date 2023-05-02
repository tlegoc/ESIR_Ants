#include "AntBasePheromone.h"

#include <iostream>

AntBasePheromone::AntBasePheromone(Environment *env, Anthill *a) : AntBase(env, a)
{
}

void AntBasePheromone::putPheromone(float quantity)
{
    std::vector<Pheromone *> p = LocalizedEntity::perceive<Pheromone>();

    if (!p.empty())
    {
        p.back()->addQuantity(quantity);
        return;
    }

    Pheromone *p_created = new Pheromone(getEnvironment(), getPosition());
    p_created->addQuantity(quantity);
}

void AntBasePheromone::putPheromone(float quantity, AntBase *ant)
{
    std::vector<Pheromone *> p = ant->LocalizedEntity::perceive<Pheromone>();

    if (!p.empty())
    {
        p.back()->addQuantity(quantity);
        return;
    }

    Pheromone *p_created = new Pheromone(ant->getEnvironment(), ant->getPosition());
    p_created->addQuantity(quantity);
}

Pheromone *AntBasePheromone::choosePheromone()
{
    std::vector<Pheromone *> pheromones = LocalizedEntity::perceive<Pheromone>(m_direction, m_viewing_angle / 2.0f, 8.0f);

    if (pheromones.empty())
        return nullptr;

    std::vector<float> weights(pheromones.size());
    std::transform(
        pheromones.begin(), pheromones.end(), weights.begin(),
        [](const auto &in)
        { return in->getQuantity(); });

    return pheromones[MathUtils::randomChoose(weights)];
}

Pheromone *AntBasePheromone::choosePheromone(AntBase *ant)
{
    std::vector<Pheromone *> pheromones = ant->LocalizedEntity::perceive<Pheromone>(ant->getDirection(), ant->getViewingAngle() / 2.0f, 8.0f);

    if (pheromones.empty())
        return nullptr;

    std::vector<float> weights(pheromones.size());
    std::transform(
        pheromones.begin(), pheromones.end(), weights.begin(),
        [](const auto &in)
        { return in->getQuantity(); });

    return pheromones[MathUtils::randomChoose(weights)];
}