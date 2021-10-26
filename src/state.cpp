#include "headers/state.hpp"

using std::vector;

void State::add_transition(Transition transition) {
   transitions.push_back(transition);
}

vector<Transition> State::get_valid_transitions(char tape_token, char stack_token) const {
   vector<Transition> result;
   for (const Transition& transition : transitions) {
      if (transition.is_valid_transition(tape_token, stack_token)) {
         result.push_back(transition);
      }
   }
   return result;
}

const std::vector<Transition>& State::get_transitions() const {
   return transitions;
}