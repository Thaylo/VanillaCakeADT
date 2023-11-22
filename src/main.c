#include <stdio.h>
#include <stdlib.h>
#include "DataContainer.h"
#include "ListNode.h"
#include "Config.h"


/*
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
*/

int main(int argc, char ** argv)
{
    UNIT_TESTING();
    
    return 0;
}