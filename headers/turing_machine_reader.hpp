#pragma once

#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <stdexcept>

#include "headers/turing_machine.hpp"
#include "headers/debug_turing_machine.hpp"
#include "headers/state.hpp"
#include "headers/alphabet.hpp"

// Allows reading a turing machine from a file. The turing machine
// can be a TuringMachine or DebugTuringMachine depending on a debug flag
class TuringMachineReader {
    Alphabet string_alphabet;
    Alphabet tape_alphabet;
    std::map<std::string, State> states; 
    int number_of_tapes;

    public:
    static TuringMachine* read_turing_machine(std::istream& input, bool debug);
    TuringMachine* read_turing_machine_from_stream(std::istream& input, bool debug);
    
    private:
    std::string read_line(std::istream& input) const;
    std::map<std::string, State> read_states(const std::string& line) const;
    Alphabet read_alphabet(const std::string& line) const;
    void add_accepting_states(const std::string& line);
    void add_transitions(std::istream &input);
    void add_transition(const std::string& line, int id);
    Transition read_transition(const std::vector<std::string>& tokens, int id) const;
    std::vector<Action> read_actions(const std::vector<std::string>& tokens) const;
    Action read_action(char input, char move, char output) const;
    std::vector<std::string> split_whitespace(const std::string& line) const;
};

