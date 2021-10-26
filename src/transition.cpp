#include "headers/transition.hpp"

#include <iostream>

using std::string;
using std::vector;

Transition::Transition(
    int id,
    std::string destination,
    char tape_token,
    char stack_token,
    vector<char> new_stack_tokens
) : id(id),
    destination(destination),
    tape_token(tape_token),
    stack_token(stack_token),
    new_stack_tokens(new_stack_tokens) {}

bool Transition::is_epsilon() const {
    return this->tape_token == EPSILON;
}

string Transition::get_destination() const {
    return destination;
}

int Transition::get_id() const {
    return id;
}

char Transition::get_tape_token() const {
    return tape_token;
}

char Transition::get_stack_token() const {
    return stack_token;
}

vector<char> Transition::get_new_stack_tokens() const {
    return new_stack_tokens;
}

bool Transition::is_valid_transition(char tape_token, char stack_token) const {
    return (tape_token == this->tape_token || this->tape_token == EPSILON) && stack_token == this->stack_token;
}