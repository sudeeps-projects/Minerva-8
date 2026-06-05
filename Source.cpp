#include "assembler.h"
#include <fstream>
#include <iomanip>
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
	cout << "Welcome to MINERVA-8 (MINIMUM RISC-V ALTERNATE ASSEMBLY LANGUAGE)" << endl;
	CPU cpu;
	cpu.init();
	cpu.print_CPU_state();
	
	ifstream file("asm3.asm");
	string line;
	cout << "ASSEMBLY FILE READ FROM USER \n";
	cout << "--------------------------- \n \n";
	while (getline(file >> ws, line)) {
		if (line[0] == ';') {
			continue;
		}
		cout << setw(4) << setfill('0') << static_cast<int>(cpu.getMemIndx()) << " " << line << endl;
		cpu.writeMemory(line);
		
	}
	cout << "\nData in memory\n" ;
	cout << "------------------\n";
	cpu.printRam();
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