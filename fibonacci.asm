; FIBONACCI.asm
; Outputs first 10 Fibonacci numbers:
; 0 1 1 2 3 5 8 13 21 34
;
; RAM 240 = previous
; RAM 241 = current
; RAM 242 = temporary counter
; RAM 243 = output counter
; RAM 244 = calculated next value

LDA 0
STA 240

LDA 1
STA 241

LDA 10
STA 243

LABEL fibonacci

; Output previous
LDM 240
OUT

; temp counter = current
LDM 241
STA 242

; next starts as previous
LDM 240
STA 244

LABEL add_loop

; next = next + 1
LDM 244
INC
STA 244

; temp counter = temp counter - 1
LDM 242
DEC
STA 242
JNZ add_loop

; previous = current
LDM 241
STA 240

; current = next
LDM 244
STA 241

; Decrement Fibonacci output counter
LDM 243
DEC
STA 243
JNZ fibonacci

HLT