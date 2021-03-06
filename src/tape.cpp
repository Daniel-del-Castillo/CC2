#include "headers/tape.hpp"

using std::vector;
using std::deque;
using std::string;
using std::logic_error;

Tape::Tape(char blank_symbol):
    blank_symbol(blank_symbol) {
    contents.push_back(blank_symbol);
    actual_position = contents.begin();
}

void Tape::set_content(const string& contents) {
    if (contents.empty()) {
        return;
    }
    this->contents.clear();
    for(char token : contents) {
        this->contents.push_back(token);
    }
    actual_position = this->contents.begin();
}

void Tape::clear() {
    contents.clear();
    contents.push_back(blank_symbol);
    actual_position = contents.begin();
}

char Tape::read() const {
    return *actual_position;
}


const std::deque<char>& Tape::get_contents() const {
    return contents;    
}

const std::deque<char>::iterator& Tape::get_actual_position() const {
    return actual_position;
}

void Tape::execute_action(char token_to_write, Movement move) {
    *actual_position = token_to_write;
    switch (move) {
    case Movement::Left:
        move_left();
        break;
    case Movement::Right:
        move_right();
        break;
    case Movement::Stay:
        break;
    default:
        throw logic_error("Internal error: Invalid movement");
    }
}

void Tape::move_left() {
    if (actual_position == contents.begin()) {
        contents.push_front(blank_symbol);
    }
    actual_position--;
}

void Tape::move_right() {
    if (actual_position + 1 == contents.end()) {
        contents.push_back(blank_symbol);
    }
    actual_position++;
}