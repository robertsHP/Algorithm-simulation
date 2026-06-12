#pragma once

#include <stack>
#include <iterator>
#include "State.h"

namespace RawEngine{
    typedef std::shared_ptr<State> StateRef;

    class StateMachine {
    public :
        StateMachine() {};
        virtual ~StateMachine() {};

        void addState (StateRef newState, bool isReplacing = true);
        void removeState ();
        void storeState (StateRef state);
        void processStateChanges ();

        StateRef& getActiveState();

    public :
        StateRef storedState;

    private:
        std::stack<StateRef> states;
        StateRef newState;

        bool isRemoving;
        bool isAdding;
        bool isReplacing;
    };
}
