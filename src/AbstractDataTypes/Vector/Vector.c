#include "Vector.h"
#include <stdio.h>

struct Vector
{
    DataObject ** array;
    int maxCapacity;
    int length;
};



/*-----------------------------------------------------------------------------------------------*/
Vector *
vectorCreate()
{
    Vector * vector = malloc(sizeof(Vector));

    vector->array = NULL;
    vector-> length = 0;
    vector->maxCapacity = 0;

    return vector;
}



/*-----------------------------------------------------------------------------------------------*/
void
vectorInitialize(Vector * vector, int maxCapacity)
{
    if(vector != NULL)
    {
        vector->maxCapacity = maxCapacity;
        if(maxCapacity != 0)
        {
            vector->array = dataObjectCreatePointerArray(maxCapacity);
        }
        else
        {
            vector->array = NULL;
        }
    }
}



/*-----------------------------------------------------------------------------------------------*/
void
vectorPushBack(Vector * vector, DataObject * dataObject)
{
    if(vector != NULL && vector->array != NULL && vector->length < vector->maxCapacity)
    {
        vector->array[vector->length++] = dataObject;
    }
}



/*-----------------------------------------------------------------------------------------------*/
DataObject *
vectorPopBack(Vector * vector)
{
    if(vector != NULL && vector->array != NULL && vector->length > 0)
    {
        return vector->array[--vector->length];
    }
    else
    {
        return NULL;
    }
}



/*-----------------------------------------------------------------------------------------------*/
DataObject *
vectorPeekElementAtPositionIndex(Vector * vector, int index)
{
    if(vector != NULL && vector->array != NULL && vector->length > 0 && index < vector->length)
    {
        return vector->array[index];
    }
    else
    {
        return NULL;
    }
}



/*-----------------------------------------------------------------------------------------------*/
void
vectorSwapElementsAtPositionIndexes(Vector * vector, int index1, int index2)
{
    if(vector != NULL && vector->array != NULL && vector->length > 0)
    {
        if(index1 != index2 && index1 < vector->length && index1 < vector->length)
        {
            DataObject * dataObject = vector->array[index1];
            vector->array[index1] = vector->array[index2];
            vector->array[index2] = dataObject;
        }
    }
}



/*-----------------------------------------------------------------------------------------------*/
int
vectorGetMaxCapacity(Vector * vector)
{
    if(vector != NULL && vector->array != NULL)
    {
        return vector->maxCapacity;
    }
    else
    {
        return 0;
    }
}



/*-----------------------------------------------------------------------------------------------*/
int
vectorGetLength(Vector * vector)
{
    if(vector != NULL && vector->array != NULL)
    {
        return vector->length;
    }
    else
    {
        return 0;
    }
}



/*-----------------------------------------------------------------------------------------------*/
DataObject **
vectorGetObjectArrayPointer(Vector * vector)
{
    if(vector != NULL)
    {
        return vector->array;
    }
    else
    {
        return NULL;
    }
}



/*-----------------------------------------------------------------------------------------------*/
void
vectorDisplayWithSizeT(void * vectorPointer, size_t unusedSizeArgument)
{
    vectorDisplay(vectorPointer);
}



/*-----------------------------------------------------------------------------------------------*/
void
vectorDisplay(void * vectorPointer)
{
    Vector * vector = (Vector*) vectorPointer;
    int cnt = 0;

    printf("[");

    if (vector != NULL && vector->array != NULL)
    {
        for (int i = 0; i < vector->length; i++)
        {
            if (cnt <= 3)
            {
                dataObjectDisplay(vector->array[i]);
            }
            else if(cnt == 4)
            {
                printf(" ... ");
                break;
            }
            cnt++;
        }
    }
    printf("]\n");
}



/*-----------------------------------------------------------------------------------------------*/
void
vectorDestroy(void * vector)
{
    Vector * vectorToDestroy = (Vector *) vector;

    if (vectorToDestroy != NULL && vectorToDestroy->array != NULL)
    {
        dataObjectDestroyPointerArray(
            vectorToDestroy->array,
            vectorToDestroy->maxCapacity
        );

        vectorToDestroy->length = 0;
        vectorToDestroy->maxCapacity = 0;
    }

    free(vectorToDestroy);
}