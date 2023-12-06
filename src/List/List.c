#include "List.h"

struct List{
    ListNode * first;
};

/*-----------------------------------------------------------------------------------------------*/
List * createEmptyList()
{
    List * list = (List *) malloc(sizeof(List));

    if (list != NULL)
    {
        list->first = NULL;
    }

    return list;
}



/*-----------------------------------------------------------------------------------------------*/
int insertToFrontOfList(List * list, DataContainer * dataContainer)
{
    if (list != NULL)
    {
        ListNode * listNode = encapsulateDataContainerOnListNode(dataContainer);

        if (listNode != NULL)
        {
            setNextListNode(listNode, list->first);
            list->first = listNode;

            return SUCCESS;
        }
        else
        {
            return ERROR;
        }
    }

    return SUCCESS;
}



/*-----------------------------------------------------------------------------------------------*/
DataContainer * elementAtList(List * list, int position)
{
    DataContainer * element = NULL;
    int count = 0;

    if (list != NULL)
    {
        for (
            ListNode * nodeIterator = list->first;
            nodeIterator != NULL;
            nodeIterator = getNextListNode(nodeIterator) )
        {

            if(count == position)
            {
                element = getDataFromListNode(nodeIterator);
                break;
            }

            count++;
        }
    }

    return element;
}



/*-----------------------------------------------------------------------------------------------*/
// The data stored in the first element will be deleted by a DataContainer callback.
void removeFromFrontOfList(List * list)
{
    if (list != NULL)
    {
        if (list->first != NULL)
        {
            ListNode * secondListNode = getNextListNode(list->first);

            destroyListNode(&list->first);
            
            list->first = secondListNode;
        }
    }
}



/*-----------------------------------------------------------------------------------------------*/
// The data stored in the first element WONT be deleted by a DataContainer callback.
// ListNode that contains the DataContainer will be deallocated.
DataContainer * popFromFrontOfList(List * list)
{
    DataContainer * dataContainer = NULL;

    if (list != NULL)
    {
        if (list->first != NULL)
        {
            ListNode * secondListNode = getNextListNode(list->first);

            dataContainer = getDataFromListNode(list->first);

            free(list->first);
            
            list->first = secondListNode;
        }
    }

    return dataContainer;
}



/*-----------------------------------------------------------------------------------------------*/
int countElementsOnList(List * list)
{
    int count = 0;

    if (list != NULL)
    {
        for (
            ListNode * nodeIterator = list->first;
            nodeIterator != NULL;
            nodeIterator = getNextListNode(nodeIterator) )
        {
            count++;
        }
    }

    return count;
}



/*-----------------------------------------------------------------------------------------------*/
void displayList(List * list)
{
    if (list != NULL)
    {
        for (
            ListNode * nodeIterator = list->first;
            nodeIterator != NULL;
            nodeIterator = getNextListNode(nodeIterator)
            )
        {
            displayDataContainer(getDataFromListNode(nodeIterator));
        }
    }
}

/*-----------------------------------------------------------------------------------------------*/
void destroyList(List ** list)
{
    if (*list != NULL)
    {
        for (ListNode * node = (*list)->first; node != NULL; )
        {
            ListNode * nextNode = getNextListNode(node);
            destroyListNode(&node);
            node = nextNode;
        }

        free(*list);
        *list = NULL;
    }
}