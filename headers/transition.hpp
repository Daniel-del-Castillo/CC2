#pragma once

#include <string>
#include <vector>

#include "headers/tape.hpp"
#include "headers/action.hpp"

#define EPSILON '.'

// Represents a transition consisting of the destination state and an action
// for each tape. It also contains an id, so the transitions are easier to
// identify in the traces
class Transition {
    int id;
    std::string destination;  
    std::vector<Action> actions;
    
    public:
    Transition(
        int id,
        std::string destination,
        std::vector<Action> actions
    );
    std::string get_destination() const;
    int get_id() const;
    std::vector<Action> get_actions() const;
    bool is_valid_transition(const std::vector<char>& input_tokens) const;
};