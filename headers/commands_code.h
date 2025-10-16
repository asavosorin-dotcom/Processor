#ifndef _COMCODE_H_
#define _COMCODE_H_

enum COMMANDS{
    HLT_G   = 0 , 
    PUSH_G  = 1 , 
    MUL_G   = 2 , 
    SUB_G   = 3 , 
    OUT_G   = 4 , 
    DIV_G   = 5 , 
    ADD_G   = 6 ,
    SQRT_G  = 7 ,
    IN_G    = 8 ,
    POPR_G  = 9 ,
    PUSHR_G = 10,
    JB_G    = 11,
    JBE_G   = 12,
    JA_G    = 13,
    JAE_G   = 14,
    JE_G    = 15,
    JNE_G   = 16,
    J_G     = 17,
    CALL_G  = 18,
    RET_G   = 19,
    PUSHM_G = 20,
    POPM_G  = 21,
    DRAW_G  = 22
};

#endif