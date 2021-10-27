#include "headers/turing_machine.hpp"

using std::map;
using std::string;
using std::deque;
using std::vector;

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
    number_of_tapes(number_of_tapes) {}

void TuringMachine::check_integrity() const {
    // if (states.count(initial_state) == 0) {
    //     throw logic_error("Initial state (" + line + ") isn't part of the states");
    // }
    // if (!tape_alphabet.contains(words[1][0])) {
    //     throw logic_error(string("Token (") + words[1][0] + ") isn't registered in the tape alphabet");
    // }
    // if (!stack_alphabet.contains(words[2][0])) {
    //     throw logic_error(string("Token (") + words[2][0] + ") isn't registered in the stack alphabet");
    // }
    // if (words[2][0] == EPSILON) {
    //     throw logic_error("A transition must always consume a token from the stack");
    // }
    // if (states.count(words[3]) == 0) {
    //     throw logic_error("State (" + words[3] + ") isn't registered");
    // }
    // if (!stack_alphabet.contains(words[i][0])) {
    //     throw logic_error(string("Token (") + words[i][0] + ") isn't registered in the stack alphabet");
}

TuringMachine::~TuringMachine() {}

bool TuringMachine::check_string(const string& s) const {
    deque<char> stack;
    return check_string(s, initial_state, stack);
}

bool TuringMachine::check_string(const string& s, const string& actual_state_name, deque<char> stack) const {
    return false;
}