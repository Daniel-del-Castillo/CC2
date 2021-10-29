#include "headers/state.hpp"

using std::vector;
using std::optional;
using std::logic_error;

State::State() {}

State::State(bool is_accepting):
    is_accepting(is_accepting) {}

void State::add_transition(const Transition& new_transition) {
    if (!can_be_added(new_transition)) {
       throw logic_error("Failed to add a transition to a state");
    }
    transitions.push_back(new_transition);
}

// States ensure their integrity:
// * All the transitions will need the same number of tapes
// * Only one transition can be chosen with a certain input
bool State::can_be_added(const Transition& new_transition) {
    if (transitions.empty()) {
        return true;
    }
    if (new_transition.get_actions().size() != transitions[0].get_actions().size()) {
        return false;
    }
    for (const Transition& transition : transitions) {
        if (new_transition.get_tokens_to_read() == transition.get_tokens_to_read()) {
            return false;
        }
    }
    return true;
}

void State::set_accepting_state() {
    is_accepting = true;
}

bool State::is_accepting_state() const {
    return is_accepting;
}

optional<Transition> State::get_valid_transition(const vector<char>& input_tokens) const {
    for (const Transition& transition : transitions) {
       if (transition.is_valid_transition(input_tokens)) {
           return transition;
        }
    }
    return {};
}

const std::vector<Transition>& State::get_transitions() const {
    return transitions;
}