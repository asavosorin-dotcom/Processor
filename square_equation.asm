IN ; a
POPR RAX 
IN ; b
POPR RBX
IN ; c

POPR RCX
PUSH 0
PUSHR RAX ;

JE :5 ; Линейное уравнение
PUSHR RBX ;Начало D
PUSHR RBX
MUL
PUSH 4
PUSHR RAX
MUL
PUSHR RCX
MUL
SUB
POPR RDX
PUSHR RDX
PUSH 0
JB :1 
PUSHR RDX
PUSH 0
JE :2
PUSHR RDX ; D > 0
SQRT
POPR REX
PUSH 2 ; Выводит два корня
OUT
PUSHR RBX ; Начало наибольшего корня
PUSH -1
MUL
PUSHR REX
ADD
PUSH 2
DIV
PUSHR RAX
DIV
OUT ; Конец
PUSHR RBX ; Начало наименьшего корня
PUSH -1
MUL
PUSHR REX
SUB
PUSH 2
DIV
PUSHR RAX
DIV
OUT ; Конец
HLT

:2 ; D == 0
    PUSH 1
    PUSHR RBX
    PUSH -1 
    MUL
    PUSH 2
    DIV
    PUSHR RAX
    DIV
    PUSH 1
    OUT
    OUT
    HLT

:1 
    PUSH 0
    OUT
    HLT

:5
    PUSHR RBX
    PUSH 0
    JE :b_zero
    
    PUSH -1
    OUT
    PUSHR RCX
    PUSH -1
    MUL
    PUSHR RBX
    DIV
    OUT
    HLT

:b_zero
    PUSHR RCX 
    PUSH 0
    JE :c_zero

    PUSH 0
    OUT
    HLT

:c_zero
    PUSH 8
    OUT
    
    HLT