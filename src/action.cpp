#include "headers/action.hpp"

Action::Action(char read_token, Movement move, char written_token):
    read_token(read_token),
    move(move),
    written_token(written_token) {}

char Action::get_read_token() const {
   return read_token; 
}

Movement Action::get_movement() const {
   return move; 
}

char Action::get_written_token() const {
   return written_token; 
}