#include "processor.h"

Command_t arr_command[50] = {
                            "HLT"  , 4, HLT_G  , 
                            "PUSH" , 5, PUSH_G ,
                            "MUL"  , 4, MUL_G  , 
                            "SUB"  , 4, SUB_G  ,
                            "OUT"  , 4, OUT_G  ,
                            "DIV"  , 4, DIV_G  , 
                            "ADD"  , 4, ADD_G  ,  
                            "SQRT" , 5, SQRT_G , 
                            "IN"   , 3, IN_G   ,
                            "POPR" , 5, POPR_G , 
                            "PUSHR", 6, PUSHR_G,
                            "JB"   , 3, JB_G   ,
                            "JBE"  , 4, JBE_G  ,
                            "JA"   , 3, JA_G   ,
                            "JAE"  , 4, JAE_G  ,
                            "JE"   , 3, JE_G   ,
                            "JNE"  , 4, JNE_G  ,
};
