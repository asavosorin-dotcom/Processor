CALL :3

:5
    PUSH 14
    PUSH 14
    PUSH 3111
    MUL
    OUT
    CALL :13
    CALL :13
    CALL :13
    J :7

PUSH 1
PUSH 2
JB :5

:7
PUSH 7
OUT
HLT

:3
    PUSH 14
    PUSH 907
    MUL
    OUT
    CALL :13
    RET

:13
    PUSH 1
    PUSH 12
    ADD
    OUT
    RET