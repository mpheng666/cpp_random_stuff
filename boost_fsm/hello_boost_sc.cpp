#include <boost/statechart/simple_state.hpp>
#include <boost/statechart/state_machine.hpp>
#include <iostream>

namespace sc = boost::statechart;

struct Greeting;

struct Machine : sc::state_machine<Machine, Greeting> {};

struct Greeting : sc::simple_state<Greeting, Machine> {
    Greeting() { std::cout << "Hello boost fsm! \n"; }
    ~Greeting() { std::cout << "Bye boost fsm! \n"; }
};

int main() {

    Machine machine_test;
    machine_test.initiate();
    return 0;
}