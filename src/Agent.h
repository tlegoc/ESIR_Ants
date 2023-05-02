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

    template <class T>
    static std::vector<T *> getAllAgentsOf()
    {
        static_assert(std::is_base_of<Agent, T>::value, "type parameter of this class must derive from Agent");

        std::vector<T *> agents = {};

        for (auto it = s_agents.begin(); it != s_agents.end(); it++)
        {
            T *current = dynamic_cast<T *>(*it);
            if (current != nullptr) // If the type of the entity is the expected one, we add it in the result
            {
                agents.push_back(current);
            }
        }

        return agents;
    }

private:
    Status m_status;

    static std::set<Agent *> s_agents;
};