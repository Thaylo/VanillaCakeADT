#include "../List/ListNode.h"

struct ListNode{
    DataObject * dataObject;
    ListNode * next;
};



/*-----------------------------------------------------------------------------------------------*/
ListNode * createEmptyListNode()
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
void setDataOnListNode(
    ListNode * listNode,
    DataObject * dataObject)
{
    if (listNode != NULL)
    {
        listNode->dataObject = dataObject;
    }
}



/*-----------------------------------------------------------------------------------------------*/
ListNode * encapsulateDataObjectOnListNode(DataObject * dataObject)
{
    ListNode * listNode = createEmptyListNode();

    if (listNode != NULL)
    {
        setDataOnListNode(listNode, dataObject);
        listNode->next = NULL;
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

    if(listNode != NULL)
    {
        size += getSizeOfDataObjectInBytes(listNode->dataObject);
    }
    
    return size;
}

/*-----------------------------------------------------------------------------------------------*/
DataObject * getDataFromListNode(ListNode * listNode)
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
void clearDataObjectFromListNode(ListNode * listNode)
{
    if(listNode != NULL)
    {
        destroyDataObject(listNode->dataObject);
        listNode->dataObject = NULL;
        listNode->next = NULL;
    }
}



/*-----------------------------------------------------------------------------------------------*/
void destroyListNode(void * listNode)
{
    clearDataObjectFromListNode(listNode);
    free(listNode);
}