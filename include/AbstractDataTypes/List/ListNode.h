#ifndef LISTNODE_H
#define LISTNODE_H

#ifdef __cplusplus
extern "C" {
#endif

#include "DataObject.h"

typedef struct ListNode ListNode;

ListNode * listNodeWrapDataObject(DataObject * dataObject);

ListNode * listNodeGetNext(ListNode * listNode);

void listNodeSetNext(ListNode * listNode, ListNode * nextListNode);

size_t listNodeGetSizeInBytes(ListNode * listNode);

DataObject * listNodeGetDataObject(ListNode * listNode);

void listNodeDestroy(void * listNode);

#ifdef __cplusplus
}
#endif

#endif /* LISTNODE_H */
