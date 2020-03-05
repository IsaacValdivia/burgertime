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
            auto nextStateInfo = nextOnStateLogic();
            if (nextStateInfo.first)
            {
                currentState = nextStateInfo.second;
                nextTransitionStateLogic();
            }
        }
    }

    void initialize()
    {
        isInitialized = true;
        nextTransitionStateLogic();
    }

protected:
    virtual std::pair<bool, uint32_t> nextOnStateLogic() = 0;

    virtual void nextTransitionStateLogic() = 0;


    bool isInitialized;

    uint32_t currentState;
};
