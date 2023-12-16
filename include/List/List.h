#ifndef LIST_H
#define LIST_H

#ifdef __cplusplus
extern "C" {
#endif

#include "genericErrorCodes.h"

#include "ListNode.h"

typedef struct List List;

List * createEmptyList();

int insertToFrontOfList(List * list, DataContainer * dataContainer);

DataContainer * elementAtList(List * list, int position);

void removeFromFrontOfList(List * list);

DataContainer * popFromFrontOfList(List * list);

int countElementsOnList(List * list);

void sortList(
    List * list,
    int (*sortComparison)(DataContainer *, DataContainer *, int usingAscendingOrder),
    int usingAscendingOrder);

void displayList(List * list);

size_t getListSizeInBytes(List * list);

int isListSorted(
    List * list,
    int (*sortComparison)(DataContainer *, DataContainer *, int usingAscendingOrder),
    int usingAscendingOrder);

void destroyList(List ** List);

#ifdef __cplusplus
}
#endif

#endif /* LIST_H */
