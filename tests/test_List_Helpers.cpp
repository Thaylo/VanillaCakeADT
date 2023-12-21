#include "test_List_Helpers.h"
#include "List.h"
#include "DataContainer.h"

int populateListWithFloats(List * list, int numberOfElements, int isRandom)
{
    int status = SUCCESS;

    for(int i = 0; i < numberOfElements; ++i)
    {
        float * data = (float*) malloc(sizeof(float));
        if(data == NULL)
        {
            status = MALLOC_ERROR;
            break;
        }
        
        if(isRandom == 0)
        {
            *data = i;
        }
        else
        {
            *data = rand();
        }

        DataContainer * dataContainer = encapsulateDataOnDataContainer(
            (void*) data,
            sizeof(float),
            free,
            testHelper_floatPointerDisplayFunction);
        
        if(dataContainer == NULL)
        {
            status = MALLOC_ERROR;
            break;
        }
        insertToFrontOfList(list, dataContainer);
    }

    return status;
}

void testHelper_floatPointerDisplayFunction(void * data, size_t size)
{
    std::cout << *(float*) data << " ";
}

int compareFloats(
    DataContainer * dataContainer1,
    DataContainer * dataContainer2,
    int usingAscendingOrder)
{
    void *data1, *data2;
    size_t dummySize;

    int result = 0;

    getDataOnDataContainer(dataContainer1, &data1, &dummySize);
    getDataOnDataContainer(dataContainer2, &data2, &dummySize);

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

