#pragma once

#include <set>
#include <vector>

class Alphabet {
    std::set<char> tokens;
    
    public:
    Alphabet();
    Alphabet(std::vector<char> tokens);
    void add_token(char token);
    bool contains(char token) const;
    const std::set<char>& get_tokens() const;
};