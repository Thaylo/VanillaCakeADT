#include "test_List_Helpers.h"
#include "List.h"
#include "DataObject.h"

int populateListWithFloats(List * list, int numberOfElements, int isRandom)
{
    int status = SUCCESS;

    for(int i = 0; i < numberOfElements; ++i)
    {
        float * wrappedData = (float*) malloc(sizeof(float));
        if(wrappedData == NULL)
        {
            status = MALLOC_ERROR;
            break;
        }
        
        if(isRandom == 0)
        {
            *wrappedData = i;
        }
        else
        {
            *wrappedData = rand();
        }

        DataObject * dataObject = dataObjectWrapData(
            (void*) wrappedData,
            sizeof(float),
            free,
            testHelper_floatPointerDisplayFunction);
        
        if(dataObject == NULL)
        {
            status = MALLOC_ERROR;
            break;
        }
        listInsertToFrontOf(list, dataObject);
    }

    return status;
}


