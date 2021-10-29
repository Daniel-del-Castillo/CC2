#include "headers/transition.hpp"

#include <iostream>

using std::string;
using std::vector;
using std::logic_error;

Transition::Transition(
    std::string destination,
    std::vector<Action> actions,
    int id
) : destination(destination),
    actions(actions),
    id(id) {
       if (actions.size() < 1) {
           throw logic_error("A transition must have actions");
       }
    }

int Transition::get_id() const {
    return id;
}

string Transition::get_destination() const {
    return destination;
}

vector<Action> Transition::get_actions() const {
    return actions;
}

vector<char> Transition::get_tokens_to_read() const {
    vector<char> result;
    for (const Action& action : actions) {
        result.push_back(action.get_token_to_read());
    }
    return result;
}

vector<Movement> Transition::get_movements() const {
    vector<Movement> result;
    for (const Action& action : actions) {
        result.push_back(action.get_movement());
    }
    return result;
}

vector<char> Transition::get_tokens_to_write() const {
    vector<char> result;
    for (const Action& action : actions) {
        result.push_back(action.get_token_to_write());
    }
    return result;
}

bool Transition::is_valid_transition(const std::vector<char>& input_tokens) const {
    for (size_t i = 0; i <  input_tokens.size(); i++) {
        if (input_tokens[i] != actions[i].get_token_to_read()) {
            return false ;
        } 
    }
    return true;
}