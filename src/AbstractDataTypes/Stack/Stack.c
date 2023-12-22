#include "Stack.h"
#include "List.h"

struct Stack
{
    List * list;
};

Stack * stackCreate(void)
{
    Stack * stack = malloc(sizeof(Stack));

    if(stack != NULL)
    {
        stack->list = createEmptyList();
    }

    return stack;
}

void stackPush(Stack * stack, DataObject * data)
{
    if(stack != NULL && data != NULL)
    {
        insertToFrontOfList(stack->list, data);
    }
}

DataObject * stackPop(Stack * stack)
{
    DataObject * dataContainer = NULL;

    if(stack != NULL)
    {
        dataContainer = popFromFrontOfList(stack->list);
    }

    return dataContainer;
}

DataObject * stackPeek(Stack * stack)
{
    DataObject * dataContainer = NULL;
    int indexOfFirstPosition = 0;

    if(stack != NULL)
    {
        dataContainer = elementAtListIndex(stack->list, indexOfFirstPosition);
    }

    return dataContainer;
}

int getStackLength(Stack * stack)
{
    int stackLength = 0;

    if(stack != NULL)
    {
        stackLength = getListLength(stack->list);
    }

    return stackLength;
}

void destroyStack(void * stack)
{
    if(stack != NULL)
    {
        destroyList(((Stack *) stack)->list);
    }
    free(stack);
}