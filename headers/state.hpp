#pragma once

#include <vector>

#include "headers/transition.hpp"

// This class represents a state and is able to inform
// about which transitions can be made with a determined input
class State {
    std::vector<Transition> transitions;

    public:
    void add_transition(Transition transition);
    std::vector<Transition> get_valid_transitions(char tape_token, char stack_token) const;
    const std::vector<Transition>& get_transitions() const;
};