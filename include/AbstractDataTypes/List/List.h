#ifndef LIST_H
#define LIST_H

#ifdef __cplusplus
extern "C" {
#endif

#include "genericErrorCodes.h"

#include "ListNode.h"

typedef struct List List;

List * listCreate();

int listInsertToFrontOf(List * list, DataObject * dataObject);

DataObject * listElementAtIndexPosition(List * list, int position);

void listDeleteFromFrontOf(List * list);

DataObject * listPopFromFrontOf(List * list);

int listGetLength(List * list);

void listSort(
    List ** list,
    int (*sortComparison)(DataObject *, DataObject *, int usingAscendingOrder),
    int usingAscendingOrder);

void listDisplayWithSizeArg(void * listPointer, size_t unusedArgumentForSize);

void listDisplay(void * listPointer);

size_t listGetSizeInBytes(List * list);

int listIsSorted(List * list);

void listSetAsSorted(List * list, int status);

int listVerifyIfIsSorted(
    List * list,
    int (*sortComparison)(DataObject *, DataObject *, int usingAscendingOrder),
    int usingAscendingOrder);

int listSplitInHalves(List ** list, List ** listA, List ** listB);

int listGetLengthByCounting(List * list);

void listDestroy(void * list);

#ifdef __cplusplus
}
#endif

#endif /* LIST_H */
