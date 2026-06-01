#include "assembler.h"

// can store up to 50 labels
Label labels[50];
int labelCount = 0;
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
			uint16_t sum;
			sum = regA + regB;
			if (sum > 255) {
				carry_flag = true;
			}
			setZeroFlag(regA);
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
			cout << static_cast<int>(regA);
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
		<< "Memory Index" << static_cast<int>(memIndx) << endl;


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

		ss >> labelName;

		if (isdigit(labelName[0])) {
			ram[memIndx++] = stoi(labelName);
		}
		else {
			ram[memIndx++] = findLabel(labelName);
		}

	}
	else if (instruction == "JZ") {
		ram[memIndx++] = JZ;
		string labelName;
		ss >> labelName;
		if (isdigit(labelName[0])) {
			ram[memIndx++] = stoi(labelName);
		}
		else {
			ram[memIndx++] = findLabel(labelName);
		}
	

	}
	else if (instruction == "JMP") {
		ram[memIndx++] = JMP;
		string labelName;
		ss >> labelName;
		if (isdigit(labelName[0])) {
			ram[memIndx++] = stoi(labelName);
		}
		else {
			ram[memIndx++] = findLabel(labelName);
		}
	}
	
	else if (instruction == "LABEL") {
		string lName;
		ss >> lName;
		labels[labelCount].name = lName;
		labels[labelCount].address = memIndx;
		labelCount++;
	}
	else {
		cout << "Invalid Instruction!";
		exit(1);
	}
	

	
}


int findLabel(string labelName) {
	for (int i = 0; i < labelCount; i++) {
		if (labels[i].name == labelName) {
			return labels[i].address;
		}
		else {
			return -1;
		}
	}
}

void CPU::setZeroFlag(uint8_t reg) {
	if (reg == 0) {
		zero_flag = true;
	}
	else {
		zero_flag = false;
	}
}