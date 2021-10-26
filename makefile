CXX = g++
CXXFLAGS = -I . -Wall -Werror -Wextra -pedantic 

bin/turing_machine_emulator: src/main.cpp bin/turing_machine_reader.o bin/turing_machine.o bin/alphabet.o bin/state.o bin/transition.o
	$(CXX) $(CXXFLAGS) -o $@ $^

bin/turing_machine_reader.o: src/turing_machine_reader.cpp headers/turing_machine_reader.hpp
	$(CXX) $(CXXFLAGS) -c -o $@ src/turing_machine_reader.cpp

bin/turing_machine.o: src/turing_machine.cpp headers/turing_machine.hpp
	$(CXX) $(CXXFLAGS) -c -o $@ src/turing_machine.cpp

bin/alphabet.o: src/alphabet.cpp headers/alphabet.hpp
	$(CXX) $(CXXFLAGS) -c -o $@ src/alphabet.cpp

bin/state.o: src/state.cpp headers/state.hpp
	$(CXX) $(CXXFLAGS) -c -o $@ src/state.cpp

bin/transition.o: src/transition.cpp headers/transition.hpp
	$(CXX) $(CXXFLAGS) -c -o $@ src/transition.cpp 

run: bin/turing_machine_emulator
	bin/turing_machine_emulator

clean:
	rm bin/*
