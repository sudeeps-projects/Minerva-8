#pragma once
#include <iostream>
#include <sstream>
using namespace std;

class CPU {
private:
	uint8_t ram[256];
	uint8_t pc;
	uint8_t memIndx;
	uint8_t regA;
	uint8_t regB;
	bool zero_flag;
	bool carry_flag;
	bool hlt;
public:
	void init();
	void run();
	void print_CPU_state();
	uint8_t readMemory(uint8_t address);
	void writeMemory(uint8_t address, uint8_t value);
	void writeMemory(string str);
	void setZeroFlag(uint8_t reg);

};

struct Label {
	int address;
	string name;
};

enum oppCode {
	LDA = 0,
	LDB,
	LDM,
	ADD,
	SUB,
	STA,
	OUT,
	JNZ,
	JZ,
	JMP,
	HLT
};