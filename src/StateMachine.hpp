#pragma once

#include <array>
#include <functional>
#include <cstdint>

class StateMachine
{
public:
    StateMachine(uint32_t initialState) : isInitialized(false), currentState(initialState) {}

    void execute()
    {
        if (isInitialized)
        {
            bool isStateFinished = nextOnStateLogic();
            if (isStateFinished)
            {
                moveToNextState();
            }
        }
    }

    void initialize()
    {
        isInitialized = true;
        nextTransitionStateLogic();
    }

    virtual void moveToNextState() = 0;

    virtual bool nextOnStateLogic() = 0;

    virtual void nextTransitionStateLogic() = 0;
protected:
    bool isInitialized;

    uint32_t currentState;
};
