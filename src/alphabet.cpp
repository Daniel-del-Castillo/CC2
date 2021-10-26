#include "headers/alphabet.hpp"

using std::vector;
using std::set;

Alphabet::Alphabet() {}

Alphabet::Alphabet(vector<char> tokens) {
    for (char token: tokens) {
        add_token(token);
    }
}

void Alphabet::add_token(char token) {
    tokens.insert(token);
}

bool Alphabet::contains(char token) const {
    return tokens.count(token) == 1;
}

const set<char>& Alphabet::get_tokens() const {
    return tokens;
}