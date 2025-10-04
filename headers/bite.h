#ifndef _BITE_H_
#define _BITE_H_

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "stack.h"
#include "work_with_text.h"

StackElement_t* TextConvertToBite(const char* filename);

#endif