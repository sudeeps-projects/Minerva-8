# MINERVA-8

MINERVA-8((MINIMUM RISC-V ALTERNATE ASSEMBLY LANGUAGE) is a console-based 8-bit CPU simulator written in C++ that demonstrates how a processor executes instructions through the fetch-decode-execute cycle while showing changes to registers, memory, flags, and control flow.

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
- Console display of CPU state and memory
- Numeric and character console output

## Fetch-Decode-Execute Cycle

### Fetch

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
| `LDM` | Load a value from memory into Register A |
| `ADD` | Add Register B to Register A |
| `SUB` | Subtract Register B from Register A |
| `STA` | Store Register A in memory |
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
| `PUSH`| Push Register A contents to stack |
| `POP` | Pop stack into Reg A and update flags|
| `CALL`| Call subroutine |
| `POP` | return from subroutine to the caller|
| `HLT` | Halt execution |

## Assembler Directives

### `LABEL`

`LABEL` defines a symbolic location in an assembly program without consuming RAM.

Example:

```asm
LDA 5
LDB 5
CMP
JZ equal

LDA 70
OUTC
HLT

LABEL equal
LDA 80
OUTC
HLT

```

## Quick Start

Run an assembly program:

```bash
MINERVA-8.exe DEC.asm
```

### Step Mode

```bash
MINERVA-8.exe DEC.asm --step
```

The `--step` option pauses after each instruction and displays the current CPU state.

### RAM Mode

```bash
MINERVA-8.exe DEC.asm --ram
```
General usage:

```text
MINERVA-8.exe <program.asm> [--step] [--ram]
```



The `--ram` option displays the assembled machine code stored in RAM.

### Step Mode and RAM Mode Together

```bash
MINERVA-8.exe DEC.asm --step --ram
```

The options can also be supplied in either order:

```bash
MINERVA-8.exe DEC.asm --ram --step
```

## Example Programs

Included examples:

- `CMP.asm`
- `DEC.asm`
- `INC.asm`
- `NOT.asm`
- `OR.asm`
- `SHL.asm`
- `SHR.asm`
- `sum.asm`
- `XOR.asm`

## Step Mode Output

Example:

```text
-----------------------------
PC: 3
A : 203
B : 0
CF: 0
ZF: 0
Next Instruction: OUT
-----------------------------

Press ENTER for next instruction...
```

## RAM Mode Output

Example:

```text
Data in memory
------------------
Address          Value
0000             0
0001             204
0002             18
0003             6
0004             20
```



## Project Goal

MINERVA-8 is built to explore how a simple CPU works at a low level, including instruction encoding, registers, RAM, arithmetic and logic operations, flags, jumps, assembly parsing, and the fetch-decode-execute cycle.

MINERVA-8 implements its own instruction set, assembler, execution logic, memory model, and debugging output in C++.
