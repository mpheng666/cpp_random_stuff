#include <boost/statechart/simple_state.hpp>
#include <boost/statechart/state_machine.hpp>
#include <iostream>

#include <boost/statechart/transition.hpp>

#include <ctime>
#include <iostream>

#include <chrono>
#include <thread>

struct IElapsedTime {
    virtual double ElapsedTime() const = 0;
};

namespace sc = boost::statechart;

struct EvStartStop : sc::event<EvStartStop> {};
struct EvReset : sc::event<EvReset> {};

struct Active;

struct StopWatch : sc::state_machine<StopWatch, Active> {
    double ElapsedTime() const{
        return state_cast<const IElapsedTime &>().ElapsedTime();
    }
};

struct Stopped;

struct Active : sc::simple_state<Active, StopWatch, Stopped> {
public:
    typedef sc::transition<EvReset, Active> reactions;

    Active() : elapsed_time_(0.0) {}
    double Elapsedtime() const { return elapsed_time_; }
    double &Elapsedtime() { return elapsed_time_; }

private:
    double elapsed_time_;
};

struct Running : IElapsedTime, sc::simple_state<Running, Active> {
public:
    typedef sc::transition<EvStartStop, Stopped> reactions;
    
    Running() : start_time_(std::time(0)) {}
    ~Running() { context<Active>().Elapsedtime() = ElapsedTime(); }

    virtual double ElapsedTime() const{
        return context<Active>().Elapsedtime() +
               std::difftime(std::time(0), start_time_);
    }

private:
    std::time_t start_time_;
};

struct Stopped : IElapsedTime, sc::simple_state<Stopped, Active> {
    typedef sc::transition<EvStartStop, Running> reactions;
    virtual double ElapsedTime() const{
        return context<Active>().Elapsedtime();
    }
};


int main() {
    StopWatch stopwatch;
    stopwatch.initiate();
    std::cout << stopwatch.ElapsedTime() << "\n";
    stopwatch.process_event(EvStartStop());
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    std::cout << stopwatch.ElapsedTime() << "\n";
    stopwatch.process_event(EvStartStop());
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    std::cout << stopwatch.ElapsedTime() << "\n";
    stopwatch.process_event(EvStartStop());
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    std::cout << stopwatch.ElapsedTime() << "\n";
    stopwatch.process_event(EvReset());
    std::cout << stopwatch.ElapsedTime() << "\n";

    return 0;
}