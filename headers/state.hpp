#pragma once

#include <vector>

#include "headers/transition.hpp"

// This class represents a state and is able to inform
// about which transitions can be made with a determined input
class State {
    std::vector<Transition> transitions;
    bool is_accepting;

    public:
    State();
    State(bool is_accepting);
    void add_transition(Transition transition);
    void set_accepting_state();
    bool is_accepting_state() const;
    std::vector<Transition> get_valid_transitions(char tape_token, char stack_token) const;
    const std::vector<Transition>& get_transitions() const;
};