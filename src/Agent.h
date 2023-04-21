#pragma once

#include "Environment.h"
#include "Vector2.h"

#include <set>

class Agent : public Environment::LocalizedEntity
{
public:
    typedef enum
    {
        running,
        destroy
    } Status;

    Agent(Environment *env, const Vector2<float> &position, float radius = Environment::LocalizedEntity::defaultRadius());

    /// @brief Updates the agent
    virtual void update() = 0;

    /// @brief Set the agent's status
    void setStatus(Status status);

    /// @brief  Set the agent's status
    /// @return The agent's current status
    Status getStatus() { return m_status; }

    /// @brief  Updates every agent created, and destroys the agents listed to be destroyed
    static void simulate();

    /// @brief Called on game closed, destroys all agents
    static void finalize();

private:
    Status m_status;

    static std::set<Agent *> s_agents;
};