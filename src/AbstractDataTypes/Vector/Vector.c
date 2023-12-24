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
    vector->maxCapacity = maxCapacity;
    vector->array = dataObjectCreatePointerArray(maxCapacity);
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
    if(vector != NULL && vector->array != NULL && vector->length > 0)
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
    return vector->maxCapacity;
}



/*-----------------------------------------------------------------------------------------------*/
int
vectorGetLength(Vector * vector)
{
    return vector->length;
}



/*-----------------------------------------------------------------------------------------------*/
DataObject **
vectorGetObjectArrayPointer(Vector * vector)
{
    return vector->array;
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

    if (vector != NULL)
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