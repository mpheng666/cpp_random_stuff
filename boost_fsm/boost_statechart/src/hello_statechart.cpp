#include <boost/statechart/custom_reaction.hpp>
#include <boost/statechart/deferral.hpp>
#include <boost/statechart/event.hpp>
#include <boost/statechart/simple_state.hpp>
#include <boost/statechart/state_machine.hpp>
#include <boost/statechart/transition.hpp>
#include <iostream>

namespace sc = boost::statechart;
using namespace std;
namespace mpl = boost::mpl;
struct firstState;
struct secondState;

struct statemachine : sc::state_machine<statemachine, firstState> {
    int stateVariable;
    statemachine() : stateVariable(100) {
        cout << "StateMachine State Variable Constructor Value = "
             << stateVariable << endl;
    }
};

struct event_MoveToSecondState : sc::event<event_MoveToSecondState> {};
struct event_CheckSMVariable : sc::event<event_CheckSMVariable> {};

struct firstState : sc::simple_state<firstState, statemachine> {
    typedef sc::custom_reaction<event_MoveToSecondState> reactions;
    sc::result react(const event_MoveToSecondState &event) {
        context<statemachine>().stateVariable = 200;
        return transit<secondState>();
    }
};
struct secondState : sc::simple_state<secondState, statemachine> {
    typedef sc::custom_reaction<event_CheckSMVariable> reactions;
    sc::result react(const event_CheckSMVariable &event) {
        cout << "Inside event => event_CheckSMVariable | StateMachine State "
                "Variable Value = "
             << context<statemachine>().stateVariable << endl;
        return discard_event();
    }
};

// The Main function

int main() {
    statemachine sm;
    sm.initiate();
    sm.process_event(event_MoveToSecondState());
    sm.process_event(event_CheckSMVariable());
    return 0;
}