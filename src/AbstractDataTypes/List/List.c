#include "List.h"
#include "Stack.h"
#include <stdio.h>

struct List{
    ListNode * first, * last;
    int hasListBeenSorted;
    int length;
};


void listAppendToEndOfList(List * destination, List * source);



/*-----------------------------------------------------------------------------------------------*/
List *
listCreate()
{
    List * list = (List *) malloc(sizeof(List));

    if (list != NULL)
    {
        list->first = NULL;
        list->last = NULL;
        list->length = 0;
        list->hasListBeenSorted = 1;
    }

    return list;
}



/*-----------------------------------------------------------------------------------------------*/
int
listInsertToFrontOf(List * list, DataObject * dataObject)
{
    if (list != NULL)
    {
        ListNode * listNode = listNodeWrapDataObject(dataObject);

        if (listNode != NULL)
        {
            if (list->first == NULL)
            {
                list->first = listNode;
                list->last = listNode;
                list->hasListBeenSorted = 1;
            }
            else
            {
                listNodeSetNext(listNode, list->first);
                list->first = listNode;
                list->hasListBeenSorted = 0;
            }

            list->length++;

            return SUCCESS;
        }
        else
        {
            return ERROR;
        }
    }

    return ERROR;
}



/*-----------------------------------------------------------------------------------------------*/
int
listInsertToBackOf(List * list, DataObject * dataObject)
{
    if (list != NULL)
    {
        ListNode * listNode = listNodeWrapDataObject(dataObject);

        if (listNode != NULL)
        {
            if (list->first == NULL)
            {
                list->first = list->last = listNode;
                list->hasListBeenSorted = 1;
            }
            else
            {
                listNodeSetNext(list->last, listNode);
                list->last = listNode;
                list->hasListBeenSorted = 0;
            }

            list->length++;

            return SUCCESS;
        }
        else
        {
            return ERROR;
        }
    }

    return ERROR;
}



/*-----------------------------------------------------------------------------------------------*/
DataObject *
listElementAtIndexPosition(List * list, int position)
{
    DataObject * element = NULL;
    int count = 0;

    if (list != NULL)
    {
        for (
            ListNode * nodeIterator = list->first;
            nodeIterator != NULL;
            nodeIterator = listNodeGetNext(nodeIterator) )
        {

            if(count == position)
            {
                element = listNodeGetDataObject(nodeIterator);
                break;
            }

            count++;
        }
    }

    return element;
}



/*-----------------------------------------------------------------------------------------------*/
// The wrappedData stored in the first element will be deleted by a DataObject callback.
void
listDeleteFromFrontOf(List * list)
{
    if (list != NULL)
    {
        if (list->first != NULL)
        {
            ListNode * secondListNode = listNodeGetNext(list->first);

            listNodeDestroy(list->first);
            
            list->first = secondListNode;
            list->length--;

            if(list->length <= 1)
            {
                list->last = list->first;
            }
        }
    }
}



/*-----------------------------------------------------------------------------------------------*/
// The wrappedData stored in the first element WONT be deleted by a DataObject callback.
// ListNode that contains the DataObject will be deallocated.
DataObject *
listPopFromFrontOf(List * list)
{
    DataObject * dataObject = NULL;

    if (list != NULL)
    {
        if (list->first != NULL)
        {
            ListNode * secondListNode = listNodeGetNext(list->first);

            dataObject = listNodeGetDataObject(list->first);

            free(list->first);
            
            list->first = secondListNode;
            list->length--;

            if(list->length <= 1)
            {
                list->last = list->first;
            }
        }
    }

    return dataObject;
}



/*-----------------------------------------------------------------------------------------------*/
int
listGetLength(List * list)
{
    int count = 0;

    if (list != NULL)
    {
        count = list->length;
    }

    return count;
}



/*-----------------------------------------------------------------------------------------------*/
void
listISortedMerge(
    List ** mergedList, List ** listA, List ** listB,
    int (*sortComparison)(DataObject *, DataObject *, int),
    int usingAscendingOrder)
{
    if(*mergedList != NULL && *listA != NULL && *listB != NULL)
    {
        while(listGetLength(*listA) > 0 && listGetLength(*listB) > 0)
        {
            DataObject * a = listElementAtIndexPosition(*listA, 0);
            DataObject * b = listElementAtIndexPosition(*listB, 0);

            if(sortComparison(a, b, usingAscendingOrder) <= 0)
            {
                listInsertToBackOf(*mergedList, listPopFromFrontOf(*listA));
            }
            else
            {
                listInsertToBackOf(*mergedList, listPopFromFrontOf(*listB));
            }
        }

        if(listGetLength(*listA) > 0)
        {
            listAppendToEndOfList(*mergedList, *listA);
        }

        if(listGetLength(*listB) > 0)
        {
            listAppendToEndOfList(*mergedList, *listB);
        }

        listDestroy(*listA);
        listDestroy(*listB);
        *listA = NULL;
        *listB = NULL;

        listSetAsSorted(*mergedList, 1);
    }
}



/*-----------------------------------------------------------------------------------------------*/
void
listAppendToEndOfList(List * destination, List * source)
{
    if(destination != NULL && source != NULL)
    {
        if(destination->first == NULL)
        {
            destination->first = source->first;
            destination->last = source->last;
        }
        else
        {
            listNodeSetNext(destination->last, source->first);
            destination->last = source->last;
        }

        destination->length += source->length;

        source->first = NULL;
        source->last = NULL;
        source->length = 0;
        source->hasListBeenSorted = 0;
    }
}



/*-----------------------------------------------------------------------------------------------*/
/* sorts the linked list by changing next pointers (not data) */
void
listMergeSort(
    List ** listRef,
    int (*sortComparison)(DataObject *, DataObject *, int),
    int usingAscendingOrder)
{
    List * list = *listRef;

    listSetAsSorted(list, 0);

    const int totalListLength = listGetLength(list);

    Stack * listsToBeProcessed = stackCreate();
    
    stackStoreOneListOnTop(listsToBeProcessed, list);

    while(stackGetLength(listsToBeProcessed) > 0)
    {
        if(stackGetLength(listsToBeProcessed) == 1)
        {
            list = stackConsumeOneListFromTop(listsToBeProcessed);

            if(listIsSorted(list) != 1)
            {
                List * listA, * listB;
                listSplitInHalves(&list, &listA, &listB);
                stackStoreOneListOnTop(listsToBeProcessed, listA);
                stackStoreOneListOnTop(listsToBeProcessed, listB);
            }
            else 
            {
                stackDestroy(listsToBeProcessed);
                *listRef = list;
                break;
            }
        }
        else
        {
            List * listA = stackConsumeOneListFromTop(listsToBeProcessed);
            
            if(listIsSorted(listA) == 1)
            {
                List * listB = stackConsumeOneListFromTop(listsToBeProcessed);

                if(listIsSorted(listB) == 1)
                {
                    List * mergedList = listCreate();
                    listISortedMerge(&mergedList, &listA, &listB, sortComparison, usingAscendingOrder);
                    stackStoreOneListOnTop(listsToBeProcessed, mergedList);
                }
                else
                {
                    List * listB1, * listB2;
                    listSplitInHalves(&listB, &listB1, &listB2);
                    stackStoreOneListOnTop(listsToBeProcessed, listA);
                    stackStoreOneListOnTop(listsToBeProcessed, listB1);
                    stackStoreOneListOnTop(listsToBeProcessed, listB2);
                }
            }
            else
            {
                List * listA1, * listA2;
                listSplitInHalves(&listA, &listA1, &listA2);
                stackStoreOneListOnTop(listsToBeProcessed, listA1);
                stackStoreOneListOnTop(listsToBeProcessed, listA2);
            }
        }
    }
}



/*-----------------------------------------------------------------------------------------------*/
void
listSort(
    List ** list,
    int (*sortComparison)(DataObject *, DataObject *, int usingAscendingOrder),
    int usingAscendingOrder)
{
    listMergeSort(list, sortComparison, usingAscendingOrder);
}



/*-----------------------------------------------------------------------------------------------*/
void
listDisplayWithSizeArg(void * listPointer, size_t unusedArgumentForSize)
{
    List * list = (List*) listPointer;
    int cnt = 0;

    printf("[");

    if (list != NULL)
    {
        for (
            ListNode * nodeIterator = list->first;
            nodeIterator != NULL;
            nodeIterator = listNodeGetNext(nodeIterator)
            )
        {
            if (cnt <= 3)
            {
                dataObjectDisplay(listNodeGetDataObject(nodeIterator));
            }
            else if(cnt == 4)
            {
                printf(" ... ");
                break;
            }
            cnt++;
        }
    }

    printf("]\n");

}



/*-----------------------------------------------------------------------------------------------*/
void
listDisplay(void * list)
{
    listDisplayWithSizeArg(list, (size_t) sizeof(List));
}



/*-----------------------------------------------------------------------------------------------*/
size_t
listGetSizeInBytes(List * list)
{
    size_t size = 0;

    if (list != NULL)
    {
        for (
            ListNode * nodeIterator = list->first;
            nodeIterator != NULL;
            nodeIterator = listNodeGetNext(nodeIterator)
            )
        {
            size += listNodeGetSizeInBytes(nodeIterator);
        }
        size += sizeof(List);
    }
    return size;
}



/*-----------------------------------------------------------------------------------------------*/
int
listIsSorted(List * list)
{
    int status = 0;
    
    if(list != NULL)
    {
        if(list->length <= 1)
        {
            list->hasListBeenSorted = 1;
        }
        
        status = list->hasListBeenSorted;
    }

    return status;
}



/*-----------------------------------------------------------------------------------------------*/
void
listSetAsSorted(List * list, int status)
{
    if(list != NULL)
    {
        list->hasListBeenSorted = status;
    }
}



/*-----------------------------------------------------------------------------------------------*/
/*
The comparison function must return an integer less than, equal to, or greater than zero if the
first argument is considered to be respectively less than, equal to, or greater than the second.
*/
int
listVerifyIfIsSorted(
    List * list,
    int (*sortComparison)(DataObject *, DataObject *, int usingAscendingOrder),
    int usingAscendingOrder)
{
    int isSorted = 1;

    if (list != NULL)
    {
        if(listGetLength(list) <= 1)
        {
            return isSorted;
        }

        ListNode * nodeIterator = list->first;
        ListNode * nextNodeIterator = listNodeGetNext(list->first);

        while(nextNodeIterator != NULL)
        {
            int comparisonResult =
                sortComparison(listNodeGetDataObject(nodeIterator), listNodeGetDataObject(nextNodeIterator), usingAscendingOrder);

            if (comparisonResult > 0)
            {
                isSorted = 0;
                break;
            }

            nodeIterator = nextNodeIterator;
            nextNodeIterator = listNodeGetNext(nextNodeIterator);
        }
    }
    return isSorted;
}



/*-----------------------------------------------------------------------------------------------*/
int
listSplitInHalves(List ** list, List ** listA, List ** listB)
{
    *listA = listCreate();
    *listB = listCreate();

    if(list != NULL && *list != NULL && *listA!= NULL && *listB != NULL)
    {
        int initialListLength = listGetLength(*list);

        if(initialListLength == 1)
        {
            listInsertToFrontOf(*listA, listPopFromFrontOf(*list));
        }
        else
        {
            if(initialListLength == 2)
            {
                listInsertToFrontOf(*listA, listPopFromFrontOf(*list));
                listInsertToFrontOf(*listB, listPopFromFrontOf(*list));
            }
            else
            {
                ListNode * slow = (*list)->first;
                ListNode * fast = slow;

                while(listNodeGetNext(fast) != NULL)
                {
                    fast = listNodeGetNext(fast);
                    if(listNodeGetNext(fast) != NULL)
                    {
                        fast = listNodeGetNext(fast);
                        slow = listNodeGetNext(slow);
                    }
                    else
                    {
                        break;
                    }
                }

                (*listA)->first = (*list)->first;
                (*listA)->last = slow;
                (*listA)->hasListBeenSorted = 0;
                (*listA)->length = initialListLength/2 + initialListLength%2;

                (*listB)->first = listNodeGetNext(slow);
                listNodeSetNext(slow, NULL);
                (*listB)->last = (*list)->last;
                (*listB)->hasListBeenSorted = 0;
                (*listB)->length = initialListLength/2;
            }
        }

        (*list)->first = NULL;
        (*list)->last = NULL;
        (*list)->length = 0;
        (*list)->hasListBeenSorted = 0;
        listDestroy(*list);
        *list = NULL;

        return SUCCESS;
    }
    else
    {
        return ERROR;
    }
}



/*-----------------------------------------------------------------------------------------------*/
int
listGetLengthByCounting(List * list)
{
    int count = 0;

    if (list != NULL)
    {
        for (
            ListNode * nodeIterator = list->first;
            nodeIterator != NULL;
            nodeIterator = listNodeGetNext(nodeIterator)
            )
        {
            count++;
        }
    }
    return count;
}



/*-----------------------------------------------------------------------------------------------*/
void
listDestroy(void * list)
{
    if (list != NULL)
    {
        for (ListNode * node = ((List*) list)->first; node != NULL; )
        {
            ListNode * nextNode = listNodeGetNext(node);
            listNodeDestroy(node);
            node = nextNode;
        }
    }
    free(list);
}