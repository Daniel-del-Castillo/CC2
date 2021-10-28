#pragma once

#include "headers/tape.hpp"

// An Action represents the movement and the tokens that must be read
// and written in a certain tape to perform a transition
class Action {
    char read_token;
    Movement move;
    char written_token;
    
    public:
    Action(char read_token, Movement move, char written_token);
    char get_read_token() const;
    Movement get_movement() const;
    char get_written_token() const;
};