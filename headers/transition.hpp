#pragma once

#include <string>
#include <vector>

#define EPSILON '.'

// Represents a transition. It also contains an id, so the transitions
// are easier to identify in the traces
class Transition {
    int id;
    std::string destination;  
    char tape_token;
    char stack_token;
    std::vector<char> new_stack_tokens;
    
    public:
    Transition(
        int id,
        std::string destination,
        char tape_token,
        char stack_token,
        std::vector<char> new_stack_tokens
    );
    bool is_epsilon() const;
    std::string get_destination() const;
    int get_id() const;
    char get_tape_token() const;
    char get_stack_token() const;
    std::vector<char> get_new_stack_tokens() const;
    bool is_valid_transition(char tape_token, char stack_token) const;
};