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
    char get_tape_token() const;
    char get_stack_token() const;
    std::vector<char> get_new_stack_tokens() const;
    bool is_valid_transition(char tape_token, char stack_token) const;
};