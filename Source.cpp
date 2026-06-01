#include "assembler.h";
#include <fstream>;
/*
LDA 5
STA 100

loop:

LDM 100
OUT

LDB 1
SUB

STA 100

JNZ loop

HLT*/
int main() {
	cout << "Hello World" << endl;
	cout << ".";
	CPU cpu;
	cpu.init();
	cpu.print_CPU_state();

	ifstream file("asm1.asm");
	string line;
	while (getline(file >> ws, line)) {
		cpu.writeMemory(line);
	}


	/*cpu.writeMemory("LDA 5");
	cpu.writeMemory("STA 100");
	cpu.writeMemory("loop");
	cpu.writeMemory("LDM 100");
	cpu.writeMemory("OUT");
	cpu.writeMemory("LDB 1");
	cpu.writeMemory("SUB");
	cpu.writeMemory("STA 100");
	cpu.writeMemory("JNZ loop");*/
	cpu.run();
	cpu.print_CPU_state();

	return 0;
}