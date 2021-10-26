#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>

#include "headers/turing_machine_reader.hpp"

using std::ifstream;
using std::cout;
using std::cin;
using std::cerr;
using std::string;
using std::exception;

struct Args {
    std::string definition_file;
    std::string strings_file;
    bool debug;
    
    Args(int argc, char** argv) {
        for (int i = 1; i < argc; i++) {
            if (string(argv[i]) == "-d") {
                debug = true;
                continue;
            }
            if (definition_file.empty()) {
                definition_file = argv[i];
            } else {
                strings_file = argv[i];
            }
        }
    }
};

void print_help() {
    cout << "This program allows emulating the behaviour of a turing machine\n";
    cout << "The first argument must be the path to a file where a valid turing machine definition is stored\n";
    cout << "The second argument is optional and should be a file in which each line will be evaluated by the turing machine\n";
    cout << "If this argument isn't specified, the string will be read from the command line and \"exit\" will be reserved to exit the program\n";
    cout << "It is also possible to specify the -d option which allows printing debug information\n";
}

void enter_reading_loop(TuringMachine* turing_machine) {
    string s;
    while (true) {
        cout << "Write the string you want to check:\n";
        getline(cin, s);
        if (s == "exit") {
            return;
        }
        if (turing_machine->check_string(s)) {
            cout << "The string " + s + " belongs to the language\n";
        } else {
            cout << "The string " + s + " doesn't belong to the language\n";
        }
    }
}

void evaluate_strings_from_file(TuringMachine* turing_machine, string filename) {
    ifstream input_file(filename);
    if (!input_file.is_open()) {
        cerr << "Couldn't open the strings file\n";
        return;
    }
    string s;
    do {
        getline(input_file, s);
        if (turing_machine->check_string(s)) {
            cout << "The string " + s + " belongs to the language\n";
        } else {
            cout << "The string " + s + " doesn't belong to the language\n";
        }
    } while (!input_file.eof());
    
}

int protected_main(int argc, char** argv) {
    if (argc < 2 || argc > 4) {
        print_help();
        return 0;
    }
    Args args(argc, argv);
    if (args.definition_file.empty()) {
        print_help();
        return 0;
    }

    ifstream input_file(args.definition_file);
    if (!input_file.is_open()) {
        cerr << "Couldn't open the definition file\n";
        return 1;
    }
    TuringMachine* turing_machine =
        TuringMachineReader::read_turing_machine(input_file, args.debug);
    if (args.strings_file.empty()) {
        enter_reading_loop(turing_machine);
    } else {
        evaluate_strings_from_file(turing_machine, args.strings_file);
    }
    free(turing_machine);
    return 0;
}

int main(int argc, char** argv) {
    try {
        return protected_main(argc, argv);
    } catch (const exception& e) {
        cerr << "Something went wrong: " << e.what() << "\n";
        return 1;
    }
}