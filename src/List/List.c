#include "List.h"
#include <stdio.h>

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

ListNode * sortedMerge(
    ListNode* a, ListNode* b,
    int (*sortComparison)(DataContainer *, DataContainer *, int usingAscendingOrder),
    int usingAscendingOrder);

void frontBackSplit(ListNode* source, ListNode** frontRef, ListNode** backRef);

/* sorts the linked list by changing next pointers (not data) */
void MergeSort(
    ListNode ** headRef,
    int (*sortComparison)(DataContainer *, DataContainer *, int usingAscendingOrder),
    int usingAscendingOrder)
{
    ListNode* head = *headRef;
    ListNode* a;
    ListNode* b;
 
    /* Base case -- length 0 or 1 */
    if ((head == NULL) || (getNextListNode(head) == NULL)) {
        return;
    }
 
    /* Split head into 'a' and 'b' sublists */
    frontBackSplit(head, &a, &b);
 
    /* Recursively sort the sublists */
    MergeSort(&a, sortComparison, usingAscendingOrder);
    MergeSort(&b, sortComparison, usingAscendingOrder);
     
    /* answer = merge the two sorted lists together */
    *headRef = sortedMerge(a, b, sortComparison, usingAscendingOrder);

}
 
ListNode * sortedMerge(
    ListNode* a, ListNode* b,
    int (*sortComparison)(DataContainer *, DataContainer *, int usingAscendingOrder),
    int usingAscendingOrder)
{
    ListNode * result = NULL;
 
    /* Base cases */
    if (a == NULL)
        return (b);
    else if (b == NULL)
        return (a);

    /* Pick either a or b, and recur */
    if (sortComparison(getDataFromListNode(a), getDataFromListNode(b), usingAscendingOrder) <= 0)
    {
        result = a;
        setNextListNode(result, sortedMerge(getNextListNode(a), b, sortComparison, usingAscendingOrder));
    }
    else
    {
        result = b;
        setNextListNode(result, sortedMerge(a, getNextListNode(b), sortComparison, usingAscendingOrder));
    }

    return result;
}
 
/* UTILITY FUNCTIONS */
/* Split the listNodes of the given list into front and back halves,
    and return the two lists using the reference parameters.
    If the length is odd, the extra listNode should go in the front list.
    Uses the fast/slow pointer strategy. */
void frontBackSplit(ListNode* source, ListNode** frontRef, ListNode** backRef)
{
    ListNode* fast;
    ListNode* slow;
    slow = source;
    fast = getNextListNode(source);
 
    /* Advance 'fast' two listNodes, and advance 'slow' one listNode */
    while (fast != NULL) {
        fast = getNextListNode(fast);
        if (fast != NULL) {
            slow = getNextListNode(slow);
            fast = getNextListNode(fast);
        }
    }
 
    /* 'slow' is before the midpoint in the list, so split it in two
    at that point. */
    *frontRef = source;
    *backRef = getNextListNode(slow);
    setNextListNode(slow, NULL);
}


/*-----------------------------------------------------------------------------------------------*/
void sortList(
    List * list,
    int (*sortComparison)(DataContainer *, DataContainer *, int usingAscendingOrder),
    int usingAscendingOrder)
{
    ListNode * head = list->first;
    MergeSort(&head, sortComparison, usingAscendingOrder);
    list->first = head;
}



/*-----------------------------------------------------------------------------------------------*/
void displayList(List * list)
{
    int cnt = 0;

    printf("[");

    if (list != NULL)
    {
        for (
            ListNode * nodeIterator = list->first;
            nodeIterator != NULL;
            nodeIterator = getNextListNode(nodeIterator)
            )
        {
            if (cnt <= 3 || cnt >= countElementsOnList(list) - 3)
            {
                displayDataContainer(getDataFromListNode(nodeIterator));
            }
            else if(cnt == 4)
            {
                printf(" ... ");
            }
            cnt++;
        }
    }

    printf("]\n");

}



/*-----------------------------------------------------------------------------------------------*/
size_t getListSizeInBytes(List * list)
{
    size_t size = 0;

    if (list != NULL)
    {
        for (
            ListNode * nodeIterator = list->first;
            nodeIterator != NULL;
            nodeIterator = getNextListNode(nodeIterator)
            )
        {
            size += getSizeOfListNodeInBytes(nodeIterator);
        }
        size += sizeof(List);
    }
    return size;
}



/*-----------------------------------------------------------------------------------------------
The comparison function must return an integer less than, equal
to, or greater than zero if the first argument is considered to
be respectively less than, equal to, or greater than the second.
*/
int isListSorted(
    List * list,
    int (*sortComparison)(DataContainer *, DataContainer *, int usingAscendingOrder),
    int usingAscendingOrder)
{
    int isSorted = 1;

    if (list != NULL)
    {
        if(countElementsOnList(list) <= 1)
        {
            return isSorted;
        }

        ListNode * nodeIterator = list->first, *nextNodeIterator = getNextListNode(list->first);

        while(nextNodeIterator != NULL)
        {
            int comparisonResult =
                sortComparison(getDataFromListNode(nodeIterator), getDataFromListNode(nextNodeIterator), usingAscendingOrder);


            if (comparisonResult > 0)
            {
                isSorted = 0;
                break;
            }

            nodeIterator = nextNodeIterator;
            nextNodeIterator = getNextListNode(nextNodeIterator);
        }
    }
    return isSorted;
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