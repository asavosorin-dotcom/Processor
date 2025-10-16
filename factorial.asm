IN
POPR RAX
PUSHR RAX
CALL :factorial
OUT
HLT

:factorial
    POPR RCX
    PUSHR RCX
    PUSHR RCX
    PUSH 1
    JE :5
    
    POPR  RAX
    PUSHR RAX

    PUSHR RAX
    PUSH 1
    SUB
    CALL :factorial
    MUL
    :5
    RET
    