#pragma once

#include <iostream>
#include <iomanip>
#include <iterator>

#include "headers/turing_machine.hpp"

#define SEPARATOR "█"
#define RED "\x1B[91m"
#define GREEN "\x1B[92m"
#define BLUE "\x1B[94m"
#define YELLOW "\x1B[93m"
#define RESET_COLOR "\033[0m"

// This class contains all the code related to debugging and printing
// traces of the execution. It relies on the TuringMachine class for the actual emulation
class DebugTuringMachine : TuringMachine {
    public: 
    DebugTuringMachine(
        Alphabet string_alphabet,
        Alphabet tape_alphabet,
        std::map<std::string, State> states,
        std::string initial_state,
        int number_of_tapes,
        char blank_symbol
    );
    bool check_string(const std::string& s) override;
    
    protected:
    bool apply_transition(const std::optional<Transition>& transition);
    void print_transitions(const std::map<std::string, State>& states) const;
    std::string states_to_string(const std::map<std::string, State>& states) const;
    std::string accepting_states_to_string(const std::map<std::string, State>& states) const;
    std::string alphabet_to_string(const Alphabet& alphabet) const;
    void print_vertical_separator(int width) const;
    void print_transition(const Transition& transition, const std::string& state_name) const;
    std::string tape_to_string(const Tape& tape) const;
};