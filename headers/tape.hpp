#pragma once

#include <deque>
#include <vector>
#include <string>
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
    void set_content(const std::string& content);
    void clear();
    char read() const;
    void execute_action(char token_to_write, Movement move);
    
    private:
    void move_left();
    void move_right();
};