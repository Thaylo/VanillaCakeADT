#include "List.h"
#include "Stack.h"
#include <stdio.h>

struct List{
    ListNode * first, * last;
    int hasListBeenSorted;
    int length;
};


void appendListToEndOfList(List * destination, List * source);


/*-----------------------------------------------------------------------------------------------*/
List * createEmptyList()
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
int insertToFrontOfList(List * list, DataContainer * dataContainer)
{
    if (list != NULL)
    {
        ListNode * listNode = encapsulateDataContainerOnListNode(dataContainer);

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
                setNextListNode(listNode, list->first);
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
int insertToBackOfList(List * list, DataContainer * dataContainer)
{
    if (list != NULL)
    {
        ListNode * listNode = encapsulateDataContainerOnListNode(dataContainer);

        if (listNode != NULL)
        {
            if (list->first == NULL)
            {
                list->first = list->last = listNode;
                list->hasListBeenSorted = 1;
            }
            else
            {
                setNextListNode(list->last, listNode);
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

            destroyListNode(list->first);
            
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
            list->length--;

            if(list->length <= 1)
            {
                list->last = list->first;
            }
        }
    }

    return dataContainer;
}



/*-----------------------------------------------------------------------------------------------*/
int getListLength(List * list)
{
    int count = 0;

    if (list != NULL)
    {
        count = list->length;
    }

    return count;
}



/*-----------------------------------------------------------------------------------------------*/
List * consumeOneListFromTopOfStack(Stack * stack)
{
    List * list = NULL;

    if(stack != NULL && getStackLength(stack) > 0)
    {
        void * currentList;
        DataContainer * dataContainer;
        size_t unused;

        dataContainer = stackPop(stack);
        getDataOnDataContainer(dataContainer, &currentList, &unused);
        destroyDataContainerKeepingStoredData(dataContainer);
        
        list = (List*) currentList;
    }

    //printf("Exibindo o que foi consumido: \n");
    //displayList(list);

    return list;
}



/*-----------------------------------------------------------------------------------------------*/
void storeListOnTopOfStack(Stack * stack, List * list)
{
    if(stack != NULL && list != NULL)
    {
        DataContainer * dataContainer =
            encapsulateDataOnDataContainer(
                list, sizeof(List), destroyList, displayListWithSizeT
            );

        stackPush(stack, dataContainer);
    }
}



/*-----------------------------------------------------------------------------------------------*/
void iterativeSortedMerge(
    List ** mergedList, List ** listA, List ** listB,
    int (*sortComparison)(DataContainer *, DataContainer *, int),
    int usingAscendingOrder)
{
    if(*mergedList != NULL && *listA != NULL && *listB != NULL)
    {
        while(getListLength(*listA) > 0 && getListLength(*listB) > 0)
        {
            DataContainer * a = elementAtList(*listA, 0);
            DataContainer * b = elementAtList(*listB, 0);

            if(sortComparison(a, b, usingAscendingOrder) <= 0)
            {
                insertToBackOfList(*mergedList, popFromFrontOfList(*listA));
            }
            else
            {
                insertToBackOfList(*mergedList, popFromFrontOfList(*listB));
            }
        }

        if(getListLength(*listA) > 0)
        {
            appendListToEndOfList(*mergedList, *listA);
        }

        if(getListLength(*listB) > 0)
        {
            appendListToEndOfList(*mergedList, *listB);
        }

        destroyList(*listA);
        destroyList(*listB);
        *listA = NULL;
        *listB = NULL;

        setIsSortedStatus(*mergedList, 1);
    }
}



/*-----------------------------------------------------------------------------------------------*/
void appendListToEndOfList(List * destination, List * source)
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
            setNextListNode(destination->last, source->first);
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
void iterativeMergeSort(
    List ** listRef,
    int (*sortComparison)(DataContainer *, DataContainer *, int),
    int usingAscendingOrder)
{
    List * list = *listRef;

    setIsSortedStatus(list, 0);

    const int totalListLength = getListLength(list);

    Stack * listsToBeProcessed = stackCreate();
    
    storeListOnTopOfStack(listsToBeProcessed, list);

    while(getStackLength(listsToBeProcessed) > 0)
    {
        if(getStackLength(listsToBeProcessed) == 1)
        {
            list = consumeOneListFromTopOfStack(listsToBeProcessed);

            if(getIsSortedStatus(list) != 1)
            {
                List * listA, * listB;
                splitListInTwoHalves(&list, &listA, &listB);
                storeListOnTopOfStack(listsToBeProcessed, listA);
                storeListOnTopOfStack(listsToBeProcessed, listB);
            }
            else 
            {
                destroyStack(listsToBeProcessed);
                *listRef = list;
                break;
            }
        }
        else
        {
            List * listA = consumeOneListFromTopOfStack(listsToBeProcessed);
            
            if(getIsSortedStatus(listA) == 1)
            {
                List * listB = consumeOneListFromTopOfStack(listsToBeProcessed);

                if(getIsSortedStatus(listB) == 1)
                {
                    List * mergedList = createEmptyList();
                    iterativeSortedMerge(&mergedList, &listA, &listB, sortComparison, usingAscendingOrder);
                    storeListOnTopOfStack(listsToBeProcessed, mergedList);
                }
                else
                {
                    List * listB1, * listB2;
                    splitListInTwoHalves(&listB, &listB1, &listB2);
                    storeListOnTopOfStack(listsToBeProcessed, listA);
                    storeListOnTopOfStack(listsToBeProcessed, listB1);
                    storeListOnTopOfStack(listsToBeProcessed, listB2);
                }
            }
            else
            {
                List * listA1, * listA2;
                splitListInTwoHalves(&listA, &listA1, &listA2);
                storeListOnTopOfStack(listsToBeProcessed, listA1);
                storeListOnTopOfStack(listsToBeProcessed, listA2);
            }
        }
    }
}



/*-----------------------------------------------------------------------------------------------*/
void sortList(
    List ** list,
    int (*sortComparison)(DataContainer *, DataContainer *, int usingAscendingOrder),
    int usingAscendingOrder)
{
    iterativeMergeSort(list, sortComparison, usingAscendingOrder);
}



/*-----------------------------------------------------------------------------------------------*/
void displayListWithSizeT(void * listPointer, size_t unusedArgumentForSize)
{
    List * list = (List*) listPointer;
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
            if (cnt <= 3)
            {
                displayDataContainer(getDataFromListNode(nodeIterator));
            }
            else if(cnt == 4)
            {
                printf(" ... ");
                break;
            }
            cnt++;
        }
        displayDataContainer(getDataFromListNode(list->last));
    }

    printf("]\n");

}



/*-----------------------------------------------------------------------------------------------*/
void displayList(void * list)
{
    displayListWithSizeT(list, (size_t) sizeof(List));
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



/*-----------------------------------------------------------------------------------------------*/
int getIsSortedStatus(List * list)
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
void setIsSortedStatus(List * list, int status)
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
int verifyIfListIsSorted(
    List * list,
    int (*sortComparison)(DataContainer *, DataContainer *, int usingAscendingOrder),
    int usingAscendingOrder)
{
    int isSorted = 1;

    if (list != NULL)
    {
        if(getListLength(list) <= 1)
        {
            return isSorted;
        }

        ListNode * nodeIterator = list->first;
        ListNode * nextNodeIterator = getNextListNode(list->first);

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
int splitListInTwoHalves(List ** list, List ** listA, List ** listB)
{
    *listA = createEmptyList();
    *listB = createEmptyList();

    if(list != NULL && *list != NULL && *listA!= NULL && *listB != NULL)
    {
        int initialListLength = getListLength(*list);

        if(initialListLength == 1)
        {
            insertToFrontOfList(*listA, popFromFrontOfList(*list));
        }
        else
        {
            if(initialListLength == 2)
            {
                insertToFrontOfList(*listA, popFromFrontOfList(*list));
                insertToFrontOfList(*listB, popFromFrontOfList(*list));
            }
            else
            {
                ListNode * slow = (*list)->first;
                ListNode * fast = slow;

                while(getNextListNode(fast) != NULL)
                {
                    fast = getNextListNode(fast);
                    if(getNextListNode(fast) != NULL)
                    {
                        fast = getNextListNode(fast);
                        slow = getNextListNode(slow);
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

                (*listB)->first = getNextListNode(slow);
                setNextListNode(slow, NULL);
                (*listB)->last = (*list)->last;
                (*listB)->hasListBeenSorted = 0;
                (*listB)->length = initialListLength/2;
            }
        }

        (*list)->first = NULL;
        (*list)->last = NULL;
        (*list)->length = 0;
        (*list)->hasListBeenSorted = 0;
        destroyList(*list);
        *list = NULL;

        return SUCCESS;
    }
    else
    {
        return ERROR;
    }
}


/*-----------------------------------------------------------------------------------------------*/
int getListLengthByCounting(List * list)
{
    int count = 0;

    if (list != NULL)
    {
        for (
            ListNode * nodeIterator = list->first;
            nodeIterator != NULL;
            nodeIterator = getNextListNode(nodeIterator)
            )
        {
            count++;
        }
    }
    return count;
}

/*-----------------------------------------------------------------------------------------------*/
void destroyList(void * list)
{
    if (list != NULL)
    {
        for (ListNode * node = ((List*) list)->first; node != NULL; )
        {
            ListNode * nextNode = getNextListNode(node);
            destroyListNode(node);
            node = nextNode;
        }
    }
    free(list);
}