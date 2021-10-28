#pragma once

#include <deque>
#include <vector>
#include <stdexcept>

#define WHITE '.'

enum Movement {
    Left = 'L',
    Right = 'R',
    Stay = 'S'
};

class Tape {
    std::deque<char> contents;    
    std::deque<char>::iterator actual_position;
    
    public:
    Tape();
    Tape(const std::vector<char>& contents);
    char read() const;
    void execute_action(char token_to_write, Movement move);
    
    private:
    void move_left();
    void move_right();
};