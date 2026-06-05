; countdown example

LDA 5
STA 100

LABEL loop

LDM 100
OUT

; decrement
LDB 1
SUB

STA 100

JNZ loop