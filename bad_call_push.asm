; bad_call_push.asm
; Repeated PUSH operations to test stack overflow protection

LDA 255

LABEL loop
PUSH
DEC
JNZ loop

PUSH
HLT