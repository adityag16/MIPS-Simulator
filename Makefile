simulator: mips_instructions.o decode.o simulator.o  memory.o
	g++ bin/mips_instructions.o bin/decode.o bin/simulator.o bin/memory.o -o bin/mips_simulator

mips_instructions.o: src/mips_instructions.cpp src/mips_instructions.hpp
	g++ -c src/mips_instructions.cpp -o bin/mips_instructions.o	

simulator.o: src/simulator.cpp src/mips_instructions.hpp src/decode.hpp
	g++ -c src/simulator.cpp -o bin/simulator.o

decode.o: src/decode.cpp src/decode.hpp
	g++ -c src/decode.cpp -o bin/decode.o

memory.o: src/memory.cpp src/memory.hpp
	g++ -c src/memory.cpp -o bin/memory.o
	
	

#./prog.exe if Windows/Cygwin

clean:
	rm *.o bin/mips_simulator
# rm *.o prog.exe if Windows/Cygwin
permissions: simulator.cpp decode.cpp mips_instructions.cpp mips_instructions.hpp memory.cpp memory.hpp
	chmod +rwx simulator.cpp
	chmod +rwx decode.cpp
	chmod +rwx mips_instructions.hpp
	chmod +rwx mips_instructions.cpp
	chmod +rwx decode.hpp
	chmod +rwx jr_addu.bin
	chmod +rwx memory.hpp
	chmod +rwx memory.cpp
#structure
#target: [dependencies list ...]
#	commands #starts with a tabulation


