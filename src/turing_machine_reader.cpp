#include "headers/turing_machine_reader.hpp"

using std::istream;
using std::string;
using std::map;
using std::logic_error;
using std::vector;

TuringMachine* TuringMachineReader::read_turing_machine(std::istream& input, bool debug) {
    TuringMachineReader reader;
    return reader.read_turing_machine_from_stream(input, debug);
}

TuringMachine* TuringMachineReader::read_turing_machine_from_stream(istream& input, bool debug) {
    states = read_states(read_line(input));
    tape_alphabet = read_alphabet(read_line(input));
    tape_alphabet.add_token(EPSILON);
    stack_alphabet = read_alphabet(read_line(input));
    stack_alphabet.add_token(EPSILON);
    string initial_state = read_initial_state(read_line(input));
    char initial_stack_token = read_initial_stack_token(read_line(input));
    add_transitions(input);
    if (debug) {
        return new TuringMachine(
            tape_alphabet,
            stack_alphabet,
            states,
            initial_state,
            initial_stack_token
        );
    } else {
        return new TuringMachine(
            tape_alphabet,
            stack_alphabet,
            states,
            initial_state,
            initial_stack_token
        );
    }
}

string TuringMachineReader::read_line(istream& input) {
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

map<string, State> TuringMachineReader::read_states(const string& line) {
    map<string, State> states;
    vector<string> state_names = split_whitespace(line);
    for (const string& name: state_names) {
        states[name] = State();
    }
    return states;
}

Alphabet TuringMachineReader::read_alphabet(const string& line) {
    Alphabet result;
    vector<string> tokens = split_whitespace(line);
    for (const string& token : tokens) {
        if (token.size() != 1) {
            throw logic_error("Tokens must be characters: " + token);
        }
        result.add_token(token[0]);
    }
    return result;
}

string TuringMachineReader::read_initial_state(const std::string& line) {
    if (states.count(line) == 0) {
        throw logic_error("Initial state (" + line + ") isn't part of the states");
    }
    return line;
}

char TuringMachineReader::read_initial_stack_token(const std::string& line) {
    char initial_stack_token = line[0];
    if (!stack_alphabet.contains(initial_stack_token)) {
        throw logic_error(
            string("Initial stack token (") + initial_stack_token + ") isn't part of the stack alphabet"
        );
    }
    if (initial_stack_token == EPSILON) {
        throw logic_error("Initial stack token can't be empty (\".\")");
    }
    return initial_stack_token;
}

void TuringMachineReader::add_transitions(istream& input) {
    int counter = 1;
    while (true) {
        std::string line;
        try {
            line = read_line(input);
        } catch(const logic_error& error) {
            break;
        }
        add_transition(line, counter);
        counter++;
    }
}

void TuringMachineReader::add_transition(const std::string& line, int id) {
    vector<string> words = split_whitespace(line);
    if (words.size() < 5) {
        throw logic_error("Invalid transition" + line);
    }
    if (states.count(words[0]) == 0) {
        throw logic_error("State (" + words[0] + ") isn't registered");
    }
    if (!tape_alphabet.contains(words[1][0])) {
        throw logic_error(string("Token (") + words[1][0] + ") isn't registered in the tape alphabet");
    }
    if (!stack_alphabet.contains(words[2][0])) {
        throw logic_error(string("Token (") + words[2][0] + ") isn't registered in the stack alphabet");
    }
    if (words[2][0] == EPSILON) {
        throw logic_error("A transition must always consume a token from the stack");
    }
    if (states.count(words[3]) == 0) {
        throw logic_error("State (" + words[3] + ") isn't registered");
    }
    vector<char> tape_output;
    for (size_t i = 4; i < words.size(); i++) {
        if (!stack_alphabet.contains(words[i][0])) {
            throw logic_error(string("Token (") + words[i][0] + ") isn't registered in the stack alphabet");
        }
        tape_output.push_back(words[i][0]);
    }
    Transition transition(id, words[3], words[1][0], words[2][0], tape_output);
    states.at(words[0]).add_transition(transition);
}

vector<string> TuringMachineReader::split_whitespace(const string& line) {
    vector<string> words;    
    size_t position = 0;
    while (true) {
       size_t start = line.find_first_not_of(' ', position);
       size_t end = line.find_first_of(' ', start);
       size_t size = end;
       if (start == string::npos) {
           break;
       } else if (end != string::npos) {
           size -= start;
       }
       words.push_back(line.substr(start, size));
       if (end == string::npos) {
           break;
       }
       position = end;
    }
    return words;
}