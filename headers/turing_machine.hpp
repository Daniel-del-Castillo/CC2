#pragma once

#include <map>
#include <string>
#include <deque>

#include "headers/alphabet.hpp"
#include "headers/state.hpp"

// A class intented to emulate a turing machine
class TuringMachine {
    protected:
    Alphabet string_alphabet;
    Alphabet tape_alphabet;
    std::map<std::string, State> states;
    std::string initial_state;
    int number_of_tapes; 
    
    public: 
    TuringMachine(
        Alphabet string_alphabet,
        Alphabet tape_alphabet,
        std::map<std::string, State> states,
        std::string initial_state,
        int number_of_tapes
    );
    virtual ~TuringMachine();
    virtual bool check_string(const std::string& s) const;
    
    protected:
    void check_integrity() const;
    virtual bool check_string(const std::string& s, const std::string& actual_state, std::deque<char> stack) const;
};