#include <stdio.h>
#include <stdlib.h>
#include "DataContainer.h"

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

void runTests()
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

    destroyDataContainer(dataContainer);
}


int main(int argc, char ** argv)
{
    runTests();
    return 0;
}