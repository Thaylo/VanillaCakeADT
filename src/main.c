#include <stdio.h>
#include <stdlib.h>
#include "DataContainer.h"
#include "ListNode.h"

void displayForTests(void * data, size_t size)
{
    int * dataCastedToInteger = (int *) data;
    for(int i = 0; i < size; ++i)
    {
        int integerValue = dataCastedToInteger[i];
        printf("%d ", integerValue);
    }
    printf("\n");
}

void runDataContainerTests()
{
    int * data = (int*) malloc(sizeof(int)*3);
    for(int i = 0; i < 5; ++i)
    {
        data[i] = i;
    }

    size_t size = 3;

    DataContainer * dataContainer = encapsulateDataOnDataContainer((void*) &data[0], (size_t) 3, free, &displayForTests);
    
    void * dataPtr;
    size_t sizePtr;

    getDataOnDataContainer(
        dataContainer,
        &dataPtr,
        &sizePtr
    );

    printf("Displaying in-place values:\n");
    displayDataContainer(dataContainer);
    printf("Size = %ld\n", size);

    printf("Displaying retrieved values:\n");
    displayForTests(dataPtr, sizePtr);
    printf("Size = %ld\n", sizePtr);

    destroyDataContainer(&dataContainer);
}

void runListNodeTests()
{
    int * data = (int*) malloc(sizeof(int)*3);
    for(int i = 0; i < 5; ++i)
    {
        data[i] = i;
    }

    size_t size = 3;

    DataContainer * dataContainer = encapsulateDataOnDataContainer((void*) &data[0], (size_t) 3, free, &displayForTests);
    ListNode * listNode = encapsulateDataContainerOnListNode(dataContainer);

    DataContainer * dataContainer2 = getDataFromListNode(listNode);

    void * dataPtr;
    size_t sizePtr;

    getDataOnDataContainer(
        dataContainer2,
        &dataPtr,
        &sizePtr
    );

    printf("Displaying retrieved values:\n");
    displayForTests(dataPtr, sizePtr);
    printf("Size = %ld\n", sizePtr);

    // Do not need to destroyDataContainer(&dataContainer2);
    destroyListNode(&listNode);
}


int main(int argc, char ** argv)
{
    runDataContainerTests();
    runListNodeTests();
    return 0;
}