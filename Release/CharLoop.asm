; PRINT  Z to A example

LDA 90         ; Load ASCII value for 'Z' (90) into Reg A
STA 240        ; Store current character state in RAM [240]
LDB 64         ; Load ASCII value for  (64) into Reg B (Stop marker, one before 'A')

LABEL loop_start
LDM 240        ; Load active character into Reg A
OUTC           ; Output Reg A as an ASCII character (Z, Y, X...)
DEC            ; Dec Reg A
STA 240        ; Save it back to RAM [240]

CMP            ; Compare Reg A with Reg B (Stop marker 64)
JNZ loop_start ; If we haven't hit character 64, loop again

HLT            ; Halt execution when done