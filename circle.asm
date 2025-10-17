IN ; radius

PUSH 35 ; x0, y0
POPR RGX

PUSH 71
POPR RHX

POPR RAX
PUSHR RAX
OUT

PUSH 0
POPR RDX ; cчетчик

:cir

PUSHR RDX
PUSH 5041

JAE :end

CALL :x
PUSHR RGX
SUB
CALL :pow

CALL :y
PUSHR RGX
SUB
CALL :pow

ADD

PUSHR RAX
CALL :pow

JA :dot

PUSH 42
POPM [RDX]
CALL :inc

J :cir

:dot
    PUSHR RAX
    OUT
    PUSH 46
    POPM [RDX]
    CALL :inc

J :cir

:end
    DRAW
    HLT

:inc         ;увеличение счетчика на 1
    PUSHR RDX
    PUSH 1
    ADD
    POPR RDX
    PUSHR RDX
    OUT
    RET

:x
    PUSHR RDX
    PUSHR RHX
    REM
    RET

:y
    PUSHR RDX
    PUSHR RHX
    DIV
    RET

:pow
    POPR REX
    PUSHR REX
    PUSHR REX
    MUL
    RET

HLT