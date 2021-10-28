#include "headers/action.hpp"

Action::Action(char token_to_read, Movement move, char token_to_write):
    token_to_read(token_to_read),
    move(move),
    token_to_write(token_to_write) {}

char Action::get_token_to_read() const {
    return token_to_read; 
}

Movement Action::get_movement() const {
    return move; 
}

char Action::get_token_to_write() const {
    return token_to_write; 
}