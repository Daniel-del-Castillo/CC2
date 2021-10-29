#pragma once

#include <string>
#include <vector>
#include <stdexcept>

#include "headers/tape.hpp"
#include "headers/action.hpp"

// Represents a transition consisting of the destination state and an action
// for each tape. It also contains an id, so the transitions are easier to
// identify in the traces
class Transition {
    std::string destination;  
    std::vector<Action> actions;
    int id;
    
    public:
    Transition(
        std::string destination,
        std::vector<Action> actions,
        int id = 0
    );
    std::string get_destination() const;
    int get_id() const;
    std::vector<Action> get_actions() const;
    std::vector<char> get_tokens_to_read() const;
    bool is_valid_transition(const std::vector<char>& input_tokens) const;
};