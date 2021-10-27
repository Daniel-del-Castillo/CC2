#pragma once

#include <deque>

enum Movement {
    Left = 'L',
    Right = 'R',
    Stay = 'S'
};

class Tape {
    std::deque<char> contents;    
};