#include "Stack.h"
#include "List.h"

struct Stack
{
    List * list;
};




/*-----------------------------------------------------------------------------------------------*/
Stack *
stackCreate(void)
{
    Stack * stack = malloc(sizeof(Stack));

    if(stack != NULL)
    {
        stack->list = listCreate();
    }

    return stack;
}



/*-----------------------------------------------------------------------------------------------*/
void
stackPush(Stack * stack, DataObject * dataObject)
{
    if(stack != NULL && dataObject != NULL)
    {
        listInsertToFrontOf(stack->list, dataObject);
    }
}



/*-----------------------------------------------------------------------------------------------*/
DataObject *
stackPop(Stack * stack)
{
    DataObject * dataObject = NULL;

    if(stack != NULL)
    {
        dataObject = listPopFromFrontOf(stack->list);
    }

    return dataObject;
}



/*-----------------------------------------------------------------------------------------------*/
DataObject *
stackPeek(Stack * stack)
{
    DataObject * dataObject = NULL;
    int indexOfFirstPosition = 0;

    if(stack != NULL)
    {
        dataObject = listElementAtIndexPosition(stack->list, indexOfFirstPosition);
    }

    return dataObject;
}



/*-----------------------------------------------------------------------------------------------*/
int
stackGetLength(Stack * stack)
{
    int stackLength = 0;

    if(stack != NULL)
    {
        stackLength = listGetLength(stack->list);
    }

    return stackLength;
}



/*-----------------------------------------------------------------------------------------------*/
List *
stackConsumeOneListFromTop(Stack * stack)
{
    List * list = NULL;

    if(stack != NULL && stackGetLength(stack) > 0)
    {
        void * currentList;
        DataObject * dataObject;
        size_t unused;

        dataObject = stackPop(stack);
        dataObjectGetWrappedData(dataObject, &currentList, &unused);
        dataObjectDestroyKeepingWrappedData(dataObject);
        
        list = (List*) currentList;
    }

    return list;
}



/*-----------------------------------------------------------------------------------------------*/
void
stackStoreOneListOnTop(Stack * stack, List * list)
{
    if(stack != NULL && list != NULL)
    {
        DataObject * dataObject =
            dataObjectWrapData(
                list, listGetSizeInBytes(list), listDestroy, listDisplayWithSizeArg
            );

        stackPush(stack, dataObject);
    }
}



/*-----------------------------------------------------------------------------------------------*/
void
stackDestroy(void * stack)
{
    if(stack != NULL)
    {
        listDestroy(((Stack *) stack)->list);
    }
    free(stack);
}