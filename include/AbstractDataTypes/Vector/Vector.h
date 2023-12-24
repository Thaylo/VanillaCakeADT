#ifndef VECTOR_H
#define VECTOR_H

#ifdef __cplusplus
extern "C" {
#endif

#include "DataObject.h"
#include "genericErrorCodes.h"

typedef struct Vector Vector;

Vector * vectorCreate();

void vectorInitialize(Vector * vector, int maxCapacity);

void vectorPushBack(Vector * vector, DataObject * dataObject);

DataObject * vectorPopBack(Vector * vector);

DataObject * vectorPeekElementAtPositionIndex(Vector * vector, int index);

void vectorSwapElementsAtPositionIndexes(Vector * vector, int index1, int index2);

int vectorGetMaxCapacity(Vector * vector);

int vectorGetLength(Vector * vector);

DataObject ** vectorGetObjectArrayPointer(Vector * vector);

void vectorDisplayWithSizeT(void * vectorPointer, size_t unusedSizeArgument);

void vectorDisplay(void * vectorPointer);

void vectorDestroy(void * vector);

#ifdef __cplusplus
}
#endif

#endif /* VECTOR_H */