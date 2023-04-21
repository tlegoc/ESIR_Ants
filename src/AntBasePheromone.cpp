#include "AntBasePheromone.h"

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