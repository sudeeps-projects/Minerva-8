;nested CALL example

LDA 5
CALL first
OUT
HLT

LABEL first
INC
CALL second
RET

LABEL second
INC
RET