#ifndef STACK_H
#define STACK_H

#ifdef __cplusplus
extern "C" {
#endif

#include "DataObject.h"
#include "List.h"

typedef struct Stack Stack;

Stack * stackCreate(void);

void stackPush(Stack * stack, DataObject * dataObject);

DataObject * stackPop(Stack * stack);

DataObject * stackPeek(Stack * stack);

int stackGetLength(Stack * stack);

List * stackConsumeOneListFromTop(Stack * stack);

void stackStoreOneListOnTop(Stack * stack, List * list);

void stackDestroy(void * stack);

#ifdef __cplusplus
}
#endif

#endif /* STACK_H */