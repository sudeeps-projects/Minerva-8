#include "assembler.h"
#include <fstream>
#include <iomanip>

int main(int argc,char* argv[]) {
	cout << "Welcome to MINERVA-8 (MINIMUM RISC-V ALTERNATE ASSEMBLY LANGUAGE)" << endl;
	CPU cpu;
	bool stepMode = false;
	bool ramMode = false;

	cpu.init();
	
	
	
	if (argc < 2) {
		cout << "Usage: MINERVA-8 <program.asm>\n";
		return 1;
	}

	for (int i = 2; i < argc; i++)
	{
		string option = argv[i];

		if (option == "--step")
		{
			stepMode = true;
		}
		else if (option == "--ram")
		{
			ramMode = true;
		}
		else
		{
			cout << "Error: Unknown option '" << option << "'\n";
			cout << "Usage: MINERVA-8 <program.asm> [--step | --ram]\n";
			return 1;
		}
		
	}
	//ifstream file("CMP.asm");
	ifstream file(argv[1]);
	string line;
	cout << "ASSEMBLY FILE LOADED FROM USER \n";
	cout << "--------------------------- \n \n";
	while (getline(file >> ws, line)) {
		if (line[0] == ';') {
			continue;
		}
		cout << setw(4) << setfill('0') << static_cast<int>(cpu.getMemIndx()) << " " << line << endl;
		cpu.writeMemory(line);
		
	}
	cpu.print_CPU_state();

	if (ramMode)
	{
		cout << "\nData in memory\n";
		cout << "------------------\n";
		cpu.printRam();
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
	cpu.run(stepMode);

	return 0;
}