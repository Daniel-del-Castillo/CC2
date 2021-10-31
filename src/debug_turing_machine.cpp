#include "headers/debug_turing_machine.hpp"

using std::string;
using std::map;
using std::vector;
using std::cout;
using std::setw;
using std::to_string;
using std::optional;
using std::distance;

DebugTuringMachine::DebugTuringMachine(
    Alphabet string_alphabet,
    Alphabet tape_alphabet,
    map<string, State> states,
    string initial_state,
    int number_of_tapes
) : TuringMachine(string_alphabet, tape_alphabet, states, initial_state, number_of_tapes) {
    cout << BLUE << "Q: " << states_to_string(states) << "\n"; 
    cout << BLUE << "Σ: " << alphabet_to_string(string_alphabet) << "\n"; 
    cout << BLUE << "Γ: " << alphabet_to_string(tape_alphabet) << "\n"; 
    cout << BLUE << "S: " << YELLOW << initial_state << "\n"; 
    cout << BLUE << "White: " << YELLOW << WHITE << "\n"; 
    cout << BLUE << "Accepting states: " << accepting_states_to_string(states) << "\n"; 
    print_transitions(states);
}

string DebugTuringMachine::states_to_string(const map<string, State>& states) const {
    string result = string(GREEN) + "{ "; 
    for (auto& name_state_pair : states) {
        result += YELLOW + name_state_pair.first + GREEN + ", ";
    }
    result = result.substr(0, result.size() - 2) + " }";
    return result;
}

string DebugTuringMachine::accepting_states_to_string(const map<string, State>& states) const {
    string result = string(GREEN) + "{ "; 
    for (auto& name_state_pair : states) {
        if (name_state_pair.second.is_accepting_state()) {
            result += YELLOW + name_state_pair.first + GREEN + ", ";
        }
    }
    result = result.substr(0, result.size() - 2) + " }";
    return result;
}

string DebugTuringMachine::alphabet_to_string(const Alphabet& alphabet) const {
    string result = string(GREEN) + "{ "; 
    for (auto token : alphabet.get_tokens()) {
        result += string(YELLOW) + token + string(GREEN) + ", ";
    }
    result = result.substr(0, result.size() - 2) + " }";
    return result;
}

void DebugTuringMachine::print_transitions(const std::map<std::string, State>& states) const {
    cout << BLUE << "δ:\n"; 
    cout << std::left;
    cout << BLUE << setw(3) << "ID" << GREEN << SEPARATOR;
    cout << BLUE << setw(6) << "State" << GREEN << SEPARATOR;
    cout << BLUE << setw(15) << "Tokens to read" << GREEN << SEPARATOR;
    cout << BLUE << setw(12) << "Destination" << GREEN << SEPARATOR;
    cout << BLUE << setw(16) << "Tokens to write" << GREEN << SEPARATOR;
    cout << BLUE << setw(10) << "Movement" << RESET_COLOR << "\n";
    print_vertical_separator(66);
    for (auto& state : states) {
        for (const auto& transition : state.second.get_transitions()) {
            print_transition(transition, state.first);
        }
    }
}

void DebugTuringMachine::print_vertical_separator(int width) const {
    cout << GREEN;
    for (int i = 0; i < width; i++) {
        cout << SEPARATOR;
    }
    cout << RESET_COLOR << "\n";
}

void DebugTuringMachine::print_transition(const Transition& transition, const string& state_name) const {
    cout << std::right;
    cout << RED << setw(2) << transition.get_id() << " " << GREEN << SEPARATOR;
    cout << YELLOW << setw(5) << state_name << " " << GREEN << SEPARATOR;
    vector<char> tokens_to_read = transition.get_tokens_to_read();
    string tokens_to_read_str(tokens_to_read.begin(), tokens_to_read.end());
    cout << YELLOW << setw(14) << tokens_to_read_str << " " << GREEN << SEPARATOR;
    cout << YELLOW << setw(11) << transition.get_destination() << " " << GREEN << SEPARATOR;
    vector<char> tokens_to_write = transition.get_tokens_to_write();
    string tokens_to_write_str(tokens_to_write.begin(), tokens_to_write.end());
    cout << YELLOW << setw(15) << tokens_to_write_str << " " << GREEN << SEPARATOR;
    vector<Movement> movements = transition.get_movements();
    string movements_str(movements.begin(), movements.end());
    cout << YELLOW << setw(9) << movements_str << RESET_COLOR << " \n";
}

bool DebugTuringMachine::check_string(const string& s) {
    cout << BLUE << "\nTrace:\n";
    cout << std::left;
    cout << BLUE << setw(10) << "State" << GREEN << SEPARATOR;
    cout << BLUE << setw(47) << "Tapes" << GREEN << SEPARATOR;
    cout << BLUE << setw(15) << "Next transition" << RESET_COLOR << "\n";
    print_vertical_separator(74);
    return TuringMachine::check_string(s);
}

bool DebugTuringMachine::apply_transition(const optional<Transition>& transition) {
    cout << std::right;
    cout << YELLOW << setw(9) << actual_state << " " << GREEN << SEPARATOR;
    cout << YELLOW << setw(50) << tape_to_string(tapes[0]) << " " << GREEN << SEPARATOR;
    if (transition.has_value()) {
        cout << YELLOW << setw(15) << transition.value().get_id() << " ";
    }
    cout << "\n";
    for (size_t i = 1; i < tapes.size(); i++) {
        cout << YELLOW << setw(10) << " " << GREEN << SEPARATOR;
        cout << YELLOW << setw(50) << tape_to_string(tapes[i]) << " " << GREEN << SEPARATOR;
        cout << setw(15) << " " << "\n";
    }
    cout << GREEN << setw(13) << SEPARATOR << setw(50) << SEPARATOR << "\n" << RESET_COLOR;
    return TuringMachine::apply_transition(transition);
}

string DebugTuringMachine::tape_to_string(const Tape& tape) const {
    string result; 
    auto& contents = tape.get_contents();
    for (auto it = contents.begin(); it < contents.end(); it++) {
        result += it == tape.get_actual_position() ? SEPARATOR : " ";
        result += *it;
        result += it == tape.get_actual_position() ? SEPARATOR : " ";
    }
    return result.empty() ? " " : result;
}