# MIPS-Simulator

This is a C++ implementation of the MIPS 32 ISA as part of a project done in pairs for the Electronic and Information Engineering 2nd Year course at Imperial College London. 
The simulator is built according to the following specfication https://github.com/m8pple/arch2-2019-cw. 
An ideal simulator will pass all tests in the provided testbench and any other testbench containing only the instructions that have been implemented.

To construct the simulator use command:
`make simulator`

To construct the test bench use command:
`make testbench`

To run the simulator against the testbench use commands:
`./bin/mips_testbench ./bin/mips_simulator`

Both the simulator and testbench were implemented from scratch without the use of the pre-existing skeleton code. 

# Acknowlegdements

Jeetendra Joshi for collaborating on the implementation of both the testbench and simulator.

Olly Larkin for creating the parser used to generate the MIPS binary files from the given source files.

Dr David Thomas for contiuous support and guidance throughout the project.


