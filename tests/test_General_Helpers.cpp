#include "test_General_Helpers.h"
#include "DataObject.h"
#include <iostream>

void testHelper_floatPointerDisplayFunction(void * data, size_t size)
{
    std::cout << *(float*) data << " ";
}

int compareFloats(
    DataObject * dataObject1,
    DataObject * dataObject2,
    int usingAscendingOrder)
{
    void *data1, *data2;
    size_t dummySize;

    int result = 0;

    dataObjectGetWrappedData(dataObject1, &data1, &dummySize);
    dataObjectGetWrappedData(dataObject2, &data2, &dummySize);

    if (data1 == NULL || data2 == NULL)
    {
        return 0;
    }

    if(*(float*) data1 < * (float*) data2)
    {
        result = -1;
    }
    else if(* (float*) data1 > * (float*) data2)
    {
        result = 1;
    }
    else
    {
        result = 0;
    }

    if(usingAscendingOrder == 0) // Not Ascending Order
    {
        result = -result;
    }

    return result;

}