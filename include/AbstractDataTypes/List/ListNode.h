#ifndef LISTNODE_H
#define LISTNODE_H

#ifdef __cplusplus
extern "C" {
#endif

#include "DataContainer.h"

typedef struct ListNode ListNode;

ListNode * encapsulateDataContainerOnListNode(DataContainer * dataContainer);

ListNode * getNextListNode(ListNode * listNode);

void setNextListNode(ListNode * listNode, ListNode * nextListNode);

size_t getSizeOfListNodeInBytes(ListNode * listNode);

DataContainer * getDataFromListNode(ListNode * listNode);

void destroyListNode(void * listNode);

#ifdef __cplusplus
}
#endif

#endif /* LISTNODE_H */
