#include "headers/turing_machine.hpp"

using std::map;
using std::string;
using std::deque;
using std::vector;
using std::logic_error;

TuringMachine::TuringMachine(
    Alphabet string_alphabet,
    Alphabet tape_alphabet,
    std::map<std::string, State> states,
    std::string initial_state,
    int number_of_tapes
):
    string_alphabet(string_alphabet),
    tape_alphabet(tape_alphabet),
    states(states),
    initial_state(initial_state),
    tapes(number_of_tapes, Tape()) {}

void TuringMachine::check_integrity() const {
    if (states.count(initial_state) == 0) {
        throw logic_error("Initial state (" + initial_state + ") isn't part of the states");
    }
    if (string_alphabet.contains(WHITE)) {
        throw logic_error(string("The string alphabet can't contain the white token (") + WHITE + ")");
    }
    check_states_integrity();
}

void TuringMachine::check_states_integrity() const {
    for (auto name_state_pair : states) {
        for (auto transition : name_state_pair.second.get_transitions()) {
            check_transition_integrity(transition);
        }
    }
}

void TuringMachine::check_transition_integrity(const Transition& transition) const {
    if (states.count(transition.get_destination()) == 0) {
        throw logic_error("State (" + transition.get_destination() + ") isn't part of the defined states");
    }
    for (auto action : transition.get_actions()) {
        check_action_integrity(action);
    }
}

void TuringMachine::check_action_integrity(const Action& action) const {
    if (!tape_alphabet.contains(action.get_token_to_read())) {
        throw logic_error(string("Token \"") + action.get_token_to_read() + "\" isn't in the tape alphabet");
    }
    if (!tape_alphabet.contains(action.get_token_to_write())) {
        throw logic_error(string("Token \"") + action.get_token_to_write() + "\" isn't in the tape alphabet");
    }
}

TuringMachine::~TuringMachine() {}

bool TuringMachine::check_string(const string& s) const {
    return s[0] == '+';
}
