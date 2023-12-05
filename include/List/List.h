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

void removeFromFrontOfList(List * list);

DataContainer * popFromFrontOfList(List * list);

int countElementsOnList(List * list);

void displayList(List * list);

void destroyList(List ** List);

#ifdef __cplusplus
}
#endif

#endif /* LIST_H */
