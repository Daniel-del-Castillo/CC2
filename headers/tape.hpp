#pragma once

#include <deque>
#include <vector>
#include <string>
#include <stdexcept>

enum Movement {
    Left = 'L',
    Right = 'R',
    Stay = 'S'
};

class Tape {
    std::deque<char> contents;    
    std::deque<char>::iterator actual_position;
    char blank_symbol;
    
    public:
    Tape(char blank_symbol);
    void set_content(const std::string& content);
    void clear();
    char read() const;
    const std::deque<char>& get_contents() const;
    const std::deque<char>::iterator& get_actual_position() const;
    void execute_action(char token_to_write, Movement move);
    
    private:
    void move_left();
    void move_right();
};