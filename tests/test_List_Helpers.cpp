
#include "test_List_Helpers.h"
#include "../include/List/List.h"
#include "../include/DataContainer/DataContainer.h"

void populateListWithFloats(List * list, int numberOfElements)
{
    for(int i = 0; i < numberOfElements; ++i)
    {
        float * data = (float*) malloc(sizeof(float));
        *data = i; 
        DataContainer * dataContainer = encapsulateDataOnDataContainer(
            (void*) data,
            sizeof(float),
            free,
            testHelper_floatPointerDisplayFunction);

        insertToFrontOfList(list, dataContainer); // List = {4.0, 3.0, 2.0, 1.0, 0.0}
    }
}

void testHelper_floatPointerDisplayFunction(void * data, size_t size)
{
    std::cout << *(float*) data << "\n";
}