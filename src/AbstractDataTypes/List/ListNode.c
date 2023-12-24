#include "../List/ListNode.h"

struct ListNode{
    DataObject * dataObject;
    ListNode * next;
};



/*-----------------------------------------------------------------------------------------------*/
ListNode *
listNodeCreate()
{
    ListNode * listNode = (ListNode *) malloc(sizeof(ListNode));

    if (listNode != NULL)
    {
        listNode->dataObject = NULL;
        listNode->next = NULL;
    }

    return listNode;
}



/*-----------------------------------------------------------------------------------------------*/
void
listNodeSetDataObject(
    ListNode * listNode,
    DataObject * dataObject)
{
    if (listNode != NULL)
    {
        listNode->dataObject = dataObject;
    }
}



/*-----------------------------------------------------------------------------------------------*/
ListNode *
listNodeWrapDataObject(DataObject * dataObject)
{
    ListNode * listNode = listNodeCreate();

    if (listNode != NULL)
    {
        listNodeSetDataObject(listNode, dataObject);
        listNode->next = NULL;
    }
    return listNode;
}



/*-----------------------------------------------------------------------------------------------*/
ListNode *
listNodeGetNext(ListNode * listNode)
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
void
listNodeSetNext(ListNode * listNode, ListNode * nextListNode)
{
    if(listNode != NULL)
    {
        listNode->next = nextListNode;
    }
}



/*-----------------------------------------------------------------------------------------------*/
size_t
listNodeGetSizeInBytes(ListNode * listNode)
{
    size_t size = 0;

    size += sizeof(ListNode);

    if(listNode != NULL)
    {
        size += dataObjectGetSizeInBytes(listNode->dataObject);
    }
    
    return size;
}



/*-----------------------------------------------------------------------------------------------*/
DataObject *
listNodeGetDataObject(ListNode * listNode)
{
    DataObject * dataObject;

    if(listNode != NULL)
    {
        dataObject = listNode->dataObject;
    }
    else
    {
        dataObject = NULL;
    }

    return dataObject;
}



/*-----------------------------------------------------------------------------------------------*/
void
listNodeClearDataObject(ListNode * listNode)
{
    if(listNode != NULL)
    {
        dataObjectDestroy(listNode->dataObject);
        listNode->dataObject = NULL;
        listNode->next = NULL;
    }
}



/*-----------------------------------------------------------------------------------------------*/
void
listNodeDestroy(void * listNode)
{
    listNodeClearDataObject(listNode);
    free(listNode);
}