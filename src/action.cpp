#include "headers/action.hpp"

Action::Action(char read_token, Movement move, char written_token):
    read_token(read_token),
    move(move),
    written_token(written_token) {}