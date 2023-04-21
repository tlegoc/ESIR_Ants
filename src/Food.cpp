#include "Food.h"
#include "MathUtils.h"
#include "Renderer.h"

Food::Food(Environment *env, const Vector2<float> &position, const float quantity) : Agent(env, position, MathUtils::circleRadius(quantity)), m_max_food(quantity)
{
    m_current_food = quantity;
}

float Food::getFoodQuantity() const {
    return m_current_food;
}

float Food::collectFood(float quantity) {
    m_current_food -= quantity;

    setRadius(MathUtils::circleRadius(std::max(m_current_food, 0.0f)));
    return quantity - std::min(m_current_food, 0.0f);
}

void Food::addFood(float quantity) {
    m_current_food += quantity;
    setRadius(MathUtils::circleRadius(std::max(m_current_food, 0.0f)));
}

void Food::update() {
    if (getStatus() == Status::destroy) return;

    if (m_current_food <= 0) {
        setStatus(Status::destroy);
        return;
    }
    
    Renderer::getInstance()->drawCircle(getPosition(), getRadius(), Renderer::Color(154, 235, 38, 255));
}