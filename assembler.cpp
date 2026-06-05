#include "assembler.h"
#include <iomanip>



// can store up to 50 labels
Label unresolvedLabels[50];
Label labels[50];
int labelCount = 0;
int unresolvedCount = 0;
int findLabel(string labelName);




void CPU::init() {
	regA = 0;
	regB = 0;
	pc = 0;
	memIndx = 0;
	zero_flag = false;
	carry_flag = false;
	hlt = false;
}

void CPU::run() {
	while (hlt != true) {
		switch (ram[pc]) {
		case LDA:
			regA = ram[pc + 1];
			setZeroFlag(regA);
			pc = pc + 2;
			break;
		case LDB:
			regB = ram[pc + 1];
			pc = pc + 2;
			break;
		case LDM:
			regA = ram[ram[pc + 1]];
			setZeroFlag(regA);
			pc = pc + 2;
			break;
		case STA:
			ram[ram[pc + 1]] = regA;
			pc = pc + 2;
			break;
		case ADD:
			int sum;
			sum = regA + regB;
			if (sum > 255) {
				carry_flag = true;
			}
			setZeroFlag(regA);
			regA = sum;
			pc++;
			break;
		case SUB:
			
			if (regA < regB) {
				carry_flag = true;
			}
			regA = regA - regB;
			setZeroFlag(regA);
			pc++;
			break;
		case OUT:
	
			
			
			cout  << regA;
			
			pc++;
			break;
		case JNZ:
			setZeroFlag(regA);
			if (zero_flag != true) {
				pc = ram[pc + 1];
				break;
			}
			else {
				pc = pc + 2;
				break;
			}
		case JZ:
			setZeroFlag(regA);
			if (zero_flag == true) {
				pc = ram[pc + 1];
				break;
			}
			else {
				pc = pc + 2;
				break;
			}
		case JMP:
			pc = ram[pc + 1];
			break;
		case HLT:
		default:
			hlt = true;
		}
	
	}

	
}

void CPU::print_CPU_state() {
	

	cout << "PC; " << static_cast<int>(pc)
	 << " regA; " << static_cast<int>(regA)

	 << " regB; " << static_cast<int>(regB)
	<< " CF; " << carry_flag
		<< " ZF; " << zero_flag
		<< "ram @ pc" << static_cast<int>(ram[pc]) 
		<< "Memory Index" << static_cast<int>(memIndx) << endl << "\n";


}

uint8_t CPU::readMemory(uint8_t address) {
	return ram[address];
}

void CPU::writeMemory(uint8_t address, uint8_t value) {
	
	ram[address] = value;
}

void CPU::writeMemory(string str) {
	stringstream ss(str);
	int value;
	string instruction;
	ss >> instruction;
	
	if (instruction == "LDA") {
		ss >> value;
		ram[memIndx++] = LDA;
		ram[memIndx++] = static_cast<uint8_t>(value);

	}
	else if (instruction == "LDB") {
		ss >> value;
		ram[memIndx++] = LDB;
		ram[memIndx++] = static_cast<uint8_t>(value);
	}
	else if (instruction == "ADD") {
		ram[memIndx++] = ADD;
	}
	else if (instruction == "SUB") {
		ram[memIndx++] = SUB;
	}
	else if (instruction == "STA") {
		ss >> value;
		ram[memIndx++] = STA;
		ram[memIndx++] = static_cast<uint8_t>(value);
		
		// TODO error checking above or below ram size
	}
	else if (instruction == "LDM") {
		ss >> value;
		ram[memIndx++] = LDM;
		ram[memIndx++] = static_cast<uint8_t>(value);

	}
	else if (instruction == "HLT") {
		ram[memIndx++] = HLT;
	}
	else if (instruction == "OUT") {
		ram[memIndx++] = OUT;
	} 
	else if (instruction == "JNZ") {
		ram[memIndx++] = JNZ;
		string labelName;

		if (ss >> labelName)
		{

			if (isdigit(labelName[0])) {
				ram[memIndx++] = stoi(labelName);;
			}
			else {
				if (findLabel(labelName) == -1) {
					unresolvedLabels[unresolvedCount].name = labelName;
					unresolvedLabels[unresolvedCount].address = memIndx;
					unresolvedCount++;
				}
				else {
					ram[memIndx++] = findLabel(labelName);

				}
			}
		}
		else
		{
			cout <<instruction << " " << "no label given";
			exit(1);
		}

	}
	else if (instruction == "JZ") {
		ram[memIndx++] = JZ;
		string labelName;
		if (ss >> labelName)
		{
			if (isdigit(labelName[0])) {
				ram[memIndx++] = stoi(labelName);
			}
			else {
				if (findLabel(labelName) == -1) {
					unresolvedLabels[unresolvedCount].name = labelName;
					unresolvedLabels[unresolvedCount].address = memIndx;
					unresolvedCount++;
				}
				else {
					ram[memIndx++] = findLabel(labelName);

				}
			}
		}
		else
		{
			cout << instruction << " " << "no label given";
			exit(1);
		}

	}
	else if (instruction == "JMP") {
		ram[memIndx++] = JMP;
		string labelName;
		if (ss >> labelName)
		{
			if (isdigit(labelName[0])) {
				ram[memIndx++] = stoi(labelName);
			}
			else {
				if (findLabel(labelName) == -1) {
					unresolvedLabels[unresolvedCount].name = labelName;
					unresolvedLabels[unresolvedCount].address = memIndx;
					unresolvedCount++;
				}
				else {
					ram[memIndx++] = findLabel(labelName);

				}

			}
		}
		else
		{
			cout << instruction << " " << "no label given";
			exit(1);
		}
	}
	
	else if (instruction == "LABEL") {
		string lName;
		ss >> lName;
		labels[labelCount].name = (lName);
		labels[labelCount].address = memIndx;
		
		for (int i = 0; i < unresolvedCount; i++) {
			if (unresolvedLabels[i].name == labels[labelCount].name) {
				ram[unresolvedLabels[i].address] = labels[labelCount].address;
				unresolvedCount--;
			}
		}

		labelCount++;

	}
	else {
		cout << instruction << "Invalid Instruction!";
		exit(1);
	}
	

	
}


int findLabel(string labelName) {
	for (int i = 0; i < labelCount; i++) {
		if (labels[i].name == labelName) {
			return labels[i].address;
		}
		// The redundant else/continue was removed here
	} // <-- Loop ends here

	return -1; // <-- This must be outside the loop
}

	


void CPU::setZeroFlag(uint8_t reg) {
	if (reg == 0) {
		zero_flag = true;
	}
	else {
		zero_flag = false;
	}
}

uint8_t CPU::getMemIndx() {
	return memIndx;
}


void CPU::printRam() {
	uint8_t x = 0;
	cout << "Address \t" << " Value" << endl;
	while (x < memIndx) {
		
		cout << setw(4) << setfill('0') << static_cast<int>(x) << "\t \t " << static_cast<int>(ram[x]) << "\n";
		x++;
	}
}