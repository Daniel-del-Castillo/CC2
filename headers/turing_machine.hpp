#pragma once

#include <map>
#include <string>
#include <deque>
#include <stdexcept>
#include <optional>

#include "headers/alphabet.hpp"
#include "headers/state.hpp"
#include "headers/tape.hpp"

// A class intented to emulate a turing machine. The TM has an infinite
// number of infinite tapes and can also move (right or left) or stay still
class TuringMachine {
    protected:
    Alphabet string_alphabet;
    Alphabet tape_alphabet;
    std::map<std::string, State> states;
    std::string initial_state;
    std::string actual_state;
    char blank_symbol;
    std::vector<Tape> tapes;
    
    public: 
    TuringMachine(
        Alphabet string_alphabet,
        Alphabet tape_alphabet,
        std::map<std::string, State> states,
        std::string initial_state,
        int number_of_tapes,
        char blank_symbol
    );
    virtual ~TuringMachine();
    virtual bool check_string(const std::string& s);
    
    protected:
    void check_integrity() const;
    void check_states_integrity(const State& state, const std::string& name) const;
    void check_transition_integrity(const Transition& transition) const;
    void check_action_integrity(const Action& action) const;
    void execution_loop();
    virtual bool apply_transition(const std::optional<Transition>& transition);
    void reset_tapes();
    std::vector<char> read() const;
};