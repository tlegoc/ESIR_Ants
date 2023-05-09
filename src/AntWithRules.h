#pragma once

#include "AntBasePheromone.h"

#include "AbstractAntRule.h"
#include "AbstractRule.h"
#include "OrRule.h"
#include "Timer.h"

#include <vector>

class AntWithRules : public AntBasePheromone
{
public:
    class RuleDropFood : public AbstractAntRule
    {
    public:
        RuleDropFood(AntBase *ant) : AbstractAntRule(ant){};

        bool condition()
        {
            std::vector<Anthill *> anthills = m_ant->LocalizedEntity::perceive<Anthill>();

            return m_ant->getCurrentFood() > 0 && !anthills.empty() && std::find(anthills.begin(), anthills.end(), m_ant->getAnthill()) != anthills.end();
        }

        void action()
        {
            m_ant->dropFood(m_ant->getAnthill());
            m_ant->turnAround();

            AntBasePheromone::putPheromone(100, m_ant);

            m_ant->translate(m_ant->getDirection() * m_ant->getSpeed() * Timer::dt());
        }
    };

    class RuleGotoAnthill : public AbstractAntRule
    {
    public:
        RuleGotoAnthill(AntBase *ant) : AbstractAntRule(ant){};

        bool condition()
        {
            return m_ant->getCurrentFood() > 0;
        }

        void action()
        {
            m_ant->setTarget(m_ant->getAnthill());
            Pheromone *p = AntBasePheromone::choosePheromone(m_ant);
            if (p != nullptr)
            {
                m_ant->setTarget(p);
            }

            AntBasePheromone::putPheromone(100, m_ant);

            m_ant->translate(m_ant->getDirection() * m_ant->getSpeed() * Timer::dt());
        }
    };

    class RuleFoodOrPherFinder : public AbstractAntRule
    {
    public:
        std::vector<Food *> m_food_touching;
        std::vector<Food *> m_food_close;
        Pheromone *m_p;

        RuleFoodOrPherFinder(AntBase *ant) : AbstractAntRule(ant){};

        bool condition()
        {
            m_food_touching = m_ant->LocalizedEntity::perceive<Food>();
            m_food_close = m_ant->LocalizedEntity::perceive<Food>(m_ant->getDirection(), m_ant->getViewingAngle(), m_ant->getViewingDistance());

            m_p = AntBasePheromone::choosePheromone(m_ant);

            return !m_food_touching.empty() || !m_food_close.empty() || m_p;
        }

        void action()
        {
            if (!m_food_touching.empty())
            {
                m_ant->addFood(m_food_touching.back()->collectFood(5 - m_ant->getCurrentFood()));
            }
            else if (!m_food_close.empty())
            {
                m_ant->setTarget(m_food_close.back());
            }
            else if (m_p)
            {
                m_ant->setTarget(m_p);
            }

            m_food_touching.clear();
            m_food_close.clear();
            m_p = nullptr;

            putPheromone(10, m_ant);

            m_ant->translate(m_ant->getDirection() * m_ant->getSpeed() * Timer::dt());
        }
    };

    class RuleRandomDirection : public AbstractAntRule
    {
    public:
        RuleRandomDirection(AntBase *ant) : AbstractAntRule(ant){};

        bool condition()
        {
            return true;
        }

        void action()
        {

            float turn_angle = MathUtils::random(-MathUtils::pi / 10 * Timer::dt(), MathUtils::pi / 10 * Timer::dt());

            m_ant->turn(turn_angle);

            m_ant->translate(m_ant->getDirection() * m_ant->getSpeed() * Timer::dt());
        }
    };

    AntWithRules(Environment *env, Anthill *a) = delete;
    AntWithRules(Environment *env, Anthill *a, AbstractRule *rule1, AbstractRule *rule2);
    AntWithRules(Environment *env, Anthill *a, AbstractRule *rule);
    void update();
    void setRule(OrRule *rule);
    ~AntWithRules();

private:
    AbstractRule *m_rule;
};