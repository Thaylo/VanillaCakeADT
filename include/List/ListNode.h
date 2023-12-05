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

DataContainer * getDataFromListNode(ListNode * listNode);

void destroyListNode(ListNode ** listNode);

#ifdef __cplusplus
}
#endif

#endif /* LISTNODE_H */
