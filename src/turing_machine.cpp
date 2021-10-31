#include "headers/turing_machine.hpp"

using std::map;
using std::string;
using std::to_string;
using std::deque;
using std::vector;
using std::logic_error;
using std::optional;

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
    tapes(number_of_tapes, Tape()) {
        if(number_of_tapes < 1) {
            throw logic_error("The number of tapes must be greater than 0");
        }
        check_integrity();
    }

TuringMachine::~TuringMachine() {}

void TuringMachine::check_integrity() const {
    if (states.count(initial_state) == 0) {
        throw logic_error("Initial state (" + initial_state + 
            ") isn't part of the states");
    }
    if (string_alphabet.contains(WHITE)) {
        throw logic_error(
            string("The string alphabet can't contain the white token (") + WHITE + ")"
        );
    }
    for (auto& name_state_pair : states) {
        check_states_integrity(name_state_pair.second, name_state_pair.first);
    }
}

void TuringMachine::check_states_integrity(const State& state, const string& name) const {
    vector<Transition> transitions = state.get_transitions();
    // We only check the first transition because all of them
    // must have the same number of actions
    if (!transitions.empty() && transitions[0].get_actions().size() != tapes.size()) {
        throw logic_error("Transition (" + name + 
            ") doesn't have the correct number of actions");
    }
    for (const auto& transition : transitions) {
        check_transition_integrity(transition);
    }
}

void TuringMachine::check_transition_integrity(const Transition& transition) const {
    if (states.count(transition.get_destination()) == 0) {
        throw logic_error("State (" + transition.get_destination() + 
            ") isn't part of the defined states");
    }
    for (const auto& action : transition.get_actions()) {
        check_action_integrity(action);
    }
}

void TuringMachine::check_action_integrity(const Action& action) const {
    if (!tape_alphabet.contains(action.get_token_to_read())) {
        throw logic_error(string("Token \"") + action.get_token_to_read() + 
            "\" isn't in the tape alphabet");
    }
    if (!tape_alphabet.contains(action.get_token_to_write())) {
        throw logic_error(string("Token \"") + action.get_token_to_write() + 
            "\" isn't in the tape alphabet");
    }
}

bool TuringMachine::check_string(const string& s) {
    for (char c : s) {
        if (!string_alphabet.contains(c)) {
            return false;
        }
    }
    reset_tapes();
    tapes[0].set_content(s);
    actual_state = initial_state;
    execution_loop();
    return states.at(actual_state).is_accepting_state();
}

void TuringMachine::execution_loop() {
    optional<Transition> transition;
    do {
        transition = states[actual_state].get_valid_transition(read());
    } while (apply_transition(transition));
}

bool TuringMachine::apply_transition(const optional<Transition>& transition) {
    if (!transition.has_value()) {
        return false;
    }
    vector<Action> actions = transition.value().get_actions();
    for (size_t i = 0; i < actions.size(); i++) {
        tapes[i].execute_action(
            actions[i].get_token_to_write(),
            actions[i].get_movement()
        );
    }
    actual_state = transition.value().get_destination();
    return true;
}

void TuringMachine::reset_tapes() {
    for (Tape& tape : tapes) {
        tape.clear();
    }
}

vector<char> TuringMachine::read() const {
    vector<char> result;
    for (const auto& tape : tapes) {
        result.push_back(tape.read());    
    }
    return result;
}
