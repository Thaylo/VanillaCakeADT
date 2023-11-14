#include <stdio.h>
#include <stdlib.h>
#include "DataContainer.h"

void displayForTests(void * data, size_t size)
{
    printf("Displaying\n");
}

int main(int argc, char ** argv)
{
    DataContainer * dataContainer = createDataContainer(NULL, (size_t) 0, free, &displayForTests);
    displayDataContainer(dataContainer);
    destroyDataContainer(dataContainer);

    return 0;
}