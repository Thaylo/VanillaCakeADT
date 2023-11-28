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
    listNode->dataContainer = dataContainer;
}



/*-----------------------------------------------------------------------------------------------*/
ListNode * encapsulateDataContainerOnListNode(DataContainer * dataContainer)
{
    ListNode * listNode = createEmptyListNode();

    setDataOnListNode(listNode, dataContainer);

    return listNode;
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