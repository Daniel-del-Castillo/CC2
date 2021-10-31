#pragma once

#include "headers/tape.hpp"

// An Action represents the movement and the tokens that must be read
// and written in a certain tape to perform a transition
class Action {
    char token_to_read;
    char token_to_write;
    Movement move;
    
    public:
    Action(char token_to_read, char token_to_write, Movement move);
    char get_token_to_read() const;
    Movement get_movement() const;
    char get_token_to_write() const;
};