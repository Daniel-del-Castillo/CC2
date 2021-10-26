# CC1
## Daniel del Castillo de la Rosa
This repository contains an implementation of a pushdown automaton emulator. It was made for the Computational Complexity subject at ULL.

# Compiling
The code is in C++ and you can compile it yourself or use the makefile prepared for that matter.
```sh
make
```
**Note**: Remember to create the `bin` directory before calling `make`

# Use
You need a file defining a pushdown automaton. You can find some examples inside the `test` folder. After loading a definition the program will prompt you to write a string. The automaton will check if that string belongs to the language it recognizes. You can exit the program by writing `exit`.

Strings can also be loaded from a file when calling the program. Each line will be interpreted as a string to check.

Running with the `-d` (it stands for debug) option makes the program write a trace of the execution.
