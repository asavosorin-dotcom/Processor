IN ; radius

IN ; x0
POPR RGX

IN ; y0
POPR RIX

PUSH 900 ; длина строки
POPR RHX

POPR RAX

PUSH 0
POPR RDX ; cчетчик

:cir

PUSHR RDX 
PUSH 2430000; количество ячеек

JAE :end

CALL :x
PUSHR RGX
SUB
CALL :pow

CALL :y
PUSHR RIX
SUB
CALL :pow

ADD

PUSHR RAX
CALL :pow

JA :empty

PUSH 140
POPM [RDX]
CALL :inc

PUSH 81
POPM [RDX]
CALL :inc

PUSH 83
POPM [RDX]
CALL :inc

J :cir

:empty
    PUSH 49
    POPM [RDX]
    CALL :inc

    PUSH 56
    POPM [RDX]
    CALL :inc

    PUSH 66
    POPM [RDX]
    CALL :inc

J :cir

:end
    DRAWWIND
    HLT

:inc         ;увеличение счетчика на 1
    PUSHR RDX
    PUSH 1
    ADD
    POPR RDX
    RET

:x
    PUSHR RDX
    PUSH 3
    DIV
    PUSHR RHX
    REM
    RET

:y
    PUSHR RDX
    PUSH 3
    DIV
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