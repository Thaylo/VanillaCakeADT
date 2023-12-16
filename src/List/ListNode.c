#include "ListNode.h"

struct ListNode{
    DataContainer * dataContainer;
    ListNode * next;
};



/*-----------------------------------------------------------------------------------------------*/
ListNode * createEmptyListNode()
{
    ListNode * listNode = (ListNode *) malloc(sizeof(ListNode));

    if (listNode != NULL)
    {
        listNode->dataContainer = NULL;
        listNode->next = NULL;
    }

    return listNode;
}



/*-----------------------------------------------------------------------------------------------*/
void setDataOnListNode(
    ListNode * listNode,
    DataContainer * dataContainer)
{
    if (listNode != NULL)
    {
        listNode->dataContainer = dataContainer;
    }
}



/*-----------------------------------------------------------------------------------------------*/
ListNode * encapsulateDataContainerOnListNode(DataContainer * dataContainer)
{
    ListNode * listNode = createEmptyListNode();

    if (listNode != NULL)
    {
        setDataOnListNode(listNode, dataContainer);
    }
    return listNode;
}



/*-----------------------------------------------------------------------------------------------*/
ListNode * getNextListNode(ListNode * listNode)
{
    if(listNode != NULL)
    {
        return listNode->next;
    }
    else
    {
        return NULL;
    }
}


/*-----------------------------------------------------------------------------------------------*/
void setNextListNode(ListNode * listNode, ListNode * nextListNode)
{
    if(listNode != NULL)
    {
        listNode->next = nextListNode;
    }
}


/*-----------------------------------------------------------------------------------------------*/
size_t getSizeOfListNodeInBytes(ListNode * listNode)
{
    size_t size = 0;

    size += sizeof(ListNode);
    size += getSizeOfDataContainerInBytes(listNode->dataContainer);
    
    return size;
}

/*-----------------------------------------------------------------------------------------------*/
DataContainer * getDataFromListNode(ListNode * listNode)
{
    DataContainer * dataContainer;

    if(listNode != NULL)
    {
        dataContainer = listNode->dataContainer;
    }
    else
    {
        dataContainer = NULL;
    }

    return dataContainer;
}



/*-----------------------------------------------------------------------------------------------*/
void clearDataContainerFromListNode(ListNode * listNode)
{
    if(listNode != NULL)
    {
        destroyDataContainer(&(listNode->dataContainer));
        listNode->dataContainer = NULL;
    }
}



/*-----------------------------------------------------------------------------------------------*/
void destroyListNode(ListNode ** listNode)
{
    if(*listNode != NULL)
    {
        clearDataContainerFromListNode(*listNode);
        free(*listNode);
        *listNode = NULL;
    }
}