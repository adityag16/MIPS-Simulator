simulator: mips_instructions.o decode.o simulator.o  memory.o
	g++ bin/mips_instructions.o bin/decode.o bin/simulator.o bin/memory.o -o bin/mips_simulator

mips_instructions.o: src/mips_instructions.cpp src/mips_instructions.hpp
	mkdir -p bin
	g++ -c -g src/mips_instructions.cpp -o bin/mips_instructions.o	

simulator.o: src/simulator.cpp src/mips_instructions.hpp src/decode.hpp
	g++ -c -g src/simulator.cpp -o bin/simulator.o

decode.o: src/decode.cpp src/decode.hpp
	g++ -c -g src/decode.cpp -o bin/decode.o

memory.o: src/memory.cpp src/memory.hpp
	g++ -c -g src/memory.cpp -o bin/memory.o


testbench: main.o parser.o instructionList.o
	cp testbench/mips_testbench ./bin/
	mkdir -p parser/bin
	g++ parser/src/main.o parser/src/parser.o parser/src/instructionList.o -o parser/bin/parser

main.o: parser/src/main.cpp
	g++ --std=c++11 -c parser/src/main.cpp -o parser/src/main.o

parser.o: parser/src/parser.cpp parser/src/parser.hpp
	g++ --std=c++11 -c parser/src/parser.cpp -o parser/src/parser.o

instructionList.o: parser/src/instructionList.cpp parser/src/instructionList.hpp
	g++ --std=c++11 -c parser/src/instructionList.cpp -o parser/src/instructionList.o
#./prog.exe if Windows/Cygwin

clean:
	rm -rf bin/
	rm -f -rf parser/src/*.o parser/bin/
# rm *.o prog.exe if Windows/Cygwin
#structure
#target: [dependencies list ...]
#	commands #starts with a tabulation


