#pragma once

class AbstractRule
{
public:
    virtual void action() = 0;
    virtual bool condition() = 0;
    virtual ~AbstractRule(){};
};