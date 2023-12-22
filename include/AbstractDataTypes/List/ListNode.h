#ifndef LISTNODE_H
#define LISTNODE_H

#ifdef __cplusplus
extern "C" {
#endif

#include "DataObject.h"

typedef struct ListNode ListNode;

ListNode * encapsulateDataObjectOnListNode(DataObject * dataObject);

ListNode * getNextListNode(ListNode * listNode);

void setNextListNode(ListNode * listNode, ListNode * nextListNode);

size_t getSizeOfListNodeInBytes(ListNode * listNode);

DataObject * getDataFromListNode(ListNode * listNode);

void destroyListNode(void * listNode);

#ifdef __cplusplus
}
#endif

#endif /* LISTNODE_H */
