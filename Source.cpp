#include "assembler.h"
#include <fstream>
#include <iomanip>

int main(int argc,char* argv[]) {
	cout << "Welcome to MINERVA-8 (MINIMUM RISC-V ALTERNATE ASSEMBLY LANGUAGE)" << endl;
	CPU cpu;
	bool stepMode = false;
	bool ramMode = false;

	cpu.init();
	
	// parse the cmdline
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
	//read in the user file
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
	//print the CPU regs
	//

	if (ramMode)
	{
		cout << "\nData in memory\n";
		cout << "------------------\n";
		cpu.printRam();
	}
	
	if (stepMode)
	{
		cpu.print_CPU_state();
		cout << "\nPress ENTER to execute...";
		cin.get();
		cpu.run(stepMode);
		//Convert code into machine code and perform arithmetic and logic unit on the assembly
	}
	else
	{
		cpu.run(false);
	}
	return 0;
}

