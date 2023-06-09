#include "Agent.h"

#include <iostream>

std::set<Agent *> Agent::s_agents = {};

Agent::Agent(Environment *env, const Vector2<float> &position, float radius)
    : Environment::LocalizedEntity(env, position, radius)
{
    m_status = Status::running;
    s_agents.insert(this);
}

void Agent::setStatus(Status status)
{
    m_status = status;
}

void Agent::simulate()
{
    // std::cout << "Agent count: " << s_agents.size() << std::endl;
    auto a = s_agents.begin();
    while (a != s_agents.end())
    {
        switch ((*a)->getStatus())
        {
        case Status::running:
            (*a)->update();
            a++;
            break;
        case Status::destroy:
            delete (*a);
            a = s_agents.erase(a);
            break;
        default:
            break;
        }
    }
}

void Agent::finalize()
{
    auto a = s_agents.begin();
    while (a != s_agents.end())
    {
        delete (*a);
        a = s_agents.erase(a);
    }
}
