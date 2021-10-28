#include "headers/tape.hpp"

using std::vector;
using std::logic_error;

Tape::Tape(const vector<char>& contents) {
    for(char token : contents) {
        this->contents.push_back(token);
    }
    actual_position = this->contents.begin();
}

char Tape::read() const {
    return *actual_position;
}

void Tape::execute_action(char written_token, Movement move) {
    *actual_position = written_token;
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
        contents.push_front(WHITE);
    }
    actual_position -= 1;
}

void Tape::move_right() {
    if (actual_position + 1 == contents.end()) {
        contents.push_back(WHITE);
    }
    actual_position += 1;
}