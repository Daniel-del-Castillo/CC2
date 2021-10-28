#include "headers/transition.hpp"

#include <iostream>

using std::string;
using std::vector;

Transition::Transition(
    std::string destination,
    std::vector<Action> actions,
    int id
) : destination(destination),
    actions(actions),
    id(id) {}

int Transition::get_id() const {
    return id;
}

string Transition::get_destination() const {
    return destination;
}

vector<Action> Transition::get_actions() const {
    return actions;
}

bool Transition::is_valid_transition(const std::vector<char>& input_tokens) const {
    // TODO    
    return false;
}