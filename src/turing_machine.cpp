#include "headers/turing_machine.hpp"

using std::map;
using std::string;
using std::deque;
using std::vector;

TuringMachine::TuringMachine(
    Alphabet tape_alphabet,
    Alphabet stack_alphabet,
    map<string, State> states,
    string initial_state,
    char initial_stack_token
):
    tape_alphabet(tape_alphabet),
    stack_alphabet(stack_alphabet),
    states(states),
    initial_state(initial_state),
    initial_stack_token(initial_stack_token) {}

TuringMachine::~TuringMachine() {}

bool TuringMachine::check_string(const string& s) const {
    deque<char> stack;
    stack.push_front(initial_stack_token);
    return check_string(s, initial_state, stack);
}

bool TuringMachine::check_string(const string& s, const string& actual_state_name, deque<char> stack) const {
    State actual_state = states.at(actual_state_name);
    if (stack.empty()) {
        return s.empty();
    }
    char stack_token = stack.front();
    stack.pop_front();
    auto transitions = actual_state.get_valid_transitions(s[0], stack_token);
    for (const Transition& transition: transitions) {
        vector<char> stack_tokens = transition.get_new_stack_tokens();
        for (auto it = stack_tokens.end() - 1; it >= stack_tokens.begin(); it--) {
            if (*it != EPSILON) {
                stack.push_front(*it);
            }
        }
        string new_string = transition.is_epsilon() ? s: s.substr(1);
        if (check_string(new_string, transition.get_destination(), stack)) {
            return true;
        }
        for (char token : stack_tokens) {
            if (token != EPSILON) {
                stack.pop_front();
            }
        }
    }
    return false;
}