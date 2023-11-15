#ifndef LISTNODE_H
#define LISTNODE_H

#include "DataContainer.h"

typedef struct ListNode ListNode;

ListNode * encapsulateDataContainerOnListNode(DataContainer * dataContainer);

DataContainer * getDataFromListNode(ListNode * listNode);

void destroyListNode(ListNode ** listNode);

#endif /* LISTNODE_H */