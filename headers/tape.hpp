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
    Tape(const std::vector<char>& contents);
    char read() const;
    void execute_action(char written_token, Movement move);
    
    private:
    void move_left();
    void move_right();
};