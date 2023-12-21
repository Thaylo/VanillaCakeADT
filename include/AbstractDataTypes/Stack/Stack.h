#ifndef STACK_H
#define STACK_H

#ifdef __cplusplus
extern "C" {
#endif


#include "DataContainer.h"

typedef struct Stack Stack;

Stack * stackCreate(void);

void stackPush(Stack * stack, DataContainer * data);

DataContainer * stackPop(Stack * stack);

DataContainer * stackPeek(Stack * stack);

int getStackLength(Stack * stack);

void destroyStack(void * stack);

#ifdef __cplusplus
}
#endif

#endif /* STACK_H */