# MINERVA-8

MINERVA-8 is a visual 8-bit CPU simulator written in C++ that demonstrates how a processor executes instructions through the fetch-decode-execute cycle while showing changes to registers, memory, flags, and control flow.

The project includes a custom assembler that translates MINERVA-8 assembly language into machine code and loads the resulting instructions and data into 256 bytes of simulated RAM.

## Architecture

MINERVA-8 currently includes:

- 8-bit CPU architecture
- 256 bytes of RAM
- Program Counter (PC)
- Register A
- Register B
- Carry Flag (CF)
- Zero Flag (ZF)
- Custom instruction set
- Custom assembler
- Symbolic labels
- Visual display of CPU state and memory
- Numeric and character console output

## Fetch-Decode-Execute Cycle

The fetch unit uses the Program Counter to retrieve the next opcode from RAM.

### Decode

The decoding unit determines which instruction the opcode represents and identifies any associated operand or memory address.

### Execute

The execution unit performs the requested operation. Depending on the instruction, it can:

- modify registers
- perform arithmetic
- perform bitwise logic
- update CPU flags
- load or store memory
- change program control flow
- output values or characters

## Instruction Set

| Instruction | Description |
|---|---|
| `LDA` | Load a value into Register A |
| `LDB` | Load a value into Register B |
| `LDM` | Load a value from memory |
| `ADD` | Add Register B to Register A |
| `SUB` | Subtract Register B from Register A |
| `STA` | Store a value in memory |
| `OUT` | Output Register A as a number |
| `OUTC`| Output Register A as an ASCII character |
| `JNZ` | Jump if the Zero Flag is not set |
| `JZ`  | Jump if the Zero Flag is set |
| `JMP` | Unconditional jump |
| `AND` | Bitwise AND of Register A and Register B |
| `OR`  | Bitwise OR of Register A and Register B |
| `XOR` | Bitwise XOR of Register A and Register B |
| `SHL` | Shift Register A left by one bit |
| `SHR` | Shift Register A right by one bit |
| `NOT` | Invert every bit in Register A |
| `INC` | Increment Register A |
| `DEC` | Decrement Register A |
| `CMP` | Compare Register A and Register B and update flags |
| `HLT` | Halt execution |

## Assembler Directives

### `LABEL`

`LABEL` defines a symbolic location in the assembly program without consuming RAM.

Example:


LDA 204
LDB 204
CMP
JZ equal

LABEL fail
LDA 70
OUTC
LDA 65
OUTC
LDA 73
OUTC
LDA 76
OUTC
HLT

LABEL equal
LDA 80
OUTC
LDA 65
OUTC
LDA 83
OUTC
LDA 83
OUTC
HLT