LDA 90         ; Load ASCII 'Z'
STA 240        ; Save to RAM
LDB 64         ; Load ASCII '@' into Reg B (Stop marker)

LABEL loop_start
LDM 240        ; 1. Load the current character into Reg A
CMP            ; 2. COMPARE IMMEDIATELY (Reg A vs Reg B)
JZ end_program ; 3. JUMP OUT IF EQUAL (If we hit 64, stop!)

OUTC           ; 4. Output the character if not equal
DEC            ; 5. Decrement Reg A
STA 240        ; 6. Save new value back to RAM
JMP loop_start ; 7. Jump back to check the next character

LABEL end_program
HLT            ; Halt execution cleanly