#pragma once

#include <map>
#include <string>
#include <deque>

#include "headers/alphabet.hpp"
#include "headers/state.hpp"

// A class intented to emulate a turing machine
class TuringMachine {
    protected:
    Alphabet tape_alphabet;
    Alphabet stack_alphabet;
    std::map<std::string, State> states;
    std::string initial_state;
    char initial_stack_token;
    
    public: 
    TuringMachine(
        Alphabet tape_alphabet,
        Alphabet stack_alphabet,
        std::map<std::string, State> states,
        std::string initial_state,
        char initial_stack_token
    );
    virtual ~TuringMachine();
    virtual bool check_string(const std::string& s) const;
    
    protected:
    virtual bool check_string(const std::string& s, const std::string& actual_state, std::deque<char> stack) const;
};