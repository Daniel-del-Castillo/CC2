#include "headers/turing_machine_reader.hpp"

using std::istream;
using std::string;
using std::map;
using std::logic_error;
using std::vector;
using std::stoi;

TuringMachine* TuringMachineReader::read_turing_machine(istream& input, bool debug) {
    TuringMachineReader reader;
    return reader.read_turing_machine_from_stream(input, debug);
}

TuringMachine* TuringMachineReader::read_turing_machine_from_stream(istream& input, bool debug) {
    states = read_states(read_line(input));
    string_alphabet = read_alphabet(read_line(input));
    tape_alphabet = read_alphabet(read_line(input));
    string initial_state = split_whitespace(read_line(input))[0];
    add_accepting_states(read_line(input));
    number_of_tapes = stoi(read_line(input));
    char blank_symbol = read_line(input)[0];
    tape_alphabet.add_token(blank_symbol);
    add_transitions(input);
    if (debug) {
        return (TuringMachine*) new DebugTuringMachine(
            string_alphabet,
            tape_alphabet,
            states,
            initial_state,
            number_of_tapes,
            blank_symbol
        );
    } else {
        return new TuringMachine(
            string_alphabet,
            tape_alphabet,
            states,
            initial_state,
            number_of_tapes,
            blank_symbol
        );
    }
}

string TuringMachineReader::read_line(istream& input) const {
    string input_line;
    do {
        if (input.eof()) {
           throw logic_error("Unexpected EOF");
        }
        input_line.clear();
        getline(input, input_line);
        input_line = input_line.substr(0, input_line.find_first_of('#'));
    } while (input_line.empty());
    return input_line;
}

map<string, State> TuringMachineReader::read_states(const string& line) const {
    vector<string> tokens = split_whitespace(line);
    map<string, State> states;
    for (const string& name: tokens) {
        states[name] = State();
    }
    return states;
}

Alphabet TuringMachineReader::read_alphabet(const string& line) const {
    vector<string> tokens = split_whitespace(line);
    Alphabet result;
    for (const string& token : tokens) {
        if (token.size() != 1) {
            throw logic_error("Tokens must be characters: " + token);
        }
        result.add_token(token[0]);
    }
    return result;
}

void TuringMachineReader::add_accepting_states(const string& line) {
    vector<string> accepting_states = split_whitespace(line);
    for (const string& state_name: accepting_states) {
        if (states.count(state_name) == 0) {
            throw logic_error("State (" + state_name + ") isn't registered");
        }
        states.at(state_name).set_accepting_state();
    }
}

void TuringMachineReader::add_transitions(istream& input) {
    int counter = 1;
    while (true) {
        string line;
        try {
            line = read_line(input);
        } catch(const logic_error& error) {
            break;
        }
        add_transition(line, counter);
        counter++;
    }
}

void TuringMachineReader::add_transition(const string& line, int id) {
    vector<string> tokens = split_whitespace(line);
    // 2 tokens for the start and destination states and 3 more for each tape
    // representing the read token, the movement and the written token 
    if (tokens.size() != 2 + size_t(number_of_tapes) * 3) {
        throw logic_error("Invalid transition: " + line);
    }
    if (states.count(tokens[0]) == 0) {
        throw logic_error("State (" + tokens[0] + ") isn't registered");
    }
    Transition transition = read_transition(tokens, id);
    try {
        states.at(tokens[0]).add_transition(transition);
    } catch (logic_error& error) {
        throw logic_error("Transition \"" + line + 
            "\" has the same input as another transition from the same state");
    }
}

Transition TuringMachineReader::read_transition(const vector<string>& tokens, int id) const {
    string initial_state = tokens[0];
    string destination_state = tokens[1 + number_of_tapes];
    vector<Action> transition_actions = read_actions(tokens);
    Transition transition(destination_state, transition_actions, id);
    return transition;
}

vector<Action> TuringMachineReader::read_actions(const vector<string>& tokens) const {
    vector<Action> actions;
    for (int i = 1; i < number_of_tapes + 1; i++) {
        actions.push_back(read_action(
            tokens[i][0],
            tokens[i * 2 + number_of_tapes][0],
            tokens[i * 2 + 1 + number_of_tapes][0]
        ));
    }
    return actions; 
}

Action TuringMachineReader::read_action(char input, char output, char move) const {
    if (move != Movement::Left &&
        move != Movement::Right &&
        move != Movement::Stay) {
        throw logic_error(
            string("Token \"") + move +
            "\" must represent a movement: Right(R), Left(L) or Stay(S)"
        );
    }
    Action new_action(input, output, Movement(move));
    return new_action;
}

vector<string> TuringMachineReader::split_whitespace(const string& line) const {
    vector<string> tokens;    
    size_t position = 0;
    while (true) {
       size_t start = line.find_first_not_of(" \t", position);
       size_t end = line.find_first_of(" \t", start);
       size_t size = end;
       if (start == string::npos) {
           break;
       } else if (end != string::npos) {
           size -= start;
       }
       tokens.push_back(line.substr(start, size));
       if (end == string::npos) {
           break;
       }
       position = end;
    }
    return tokens;
}