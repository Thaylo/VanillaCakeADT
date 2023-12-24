#include "test_General_Helpers.h"
#include "test_Vector_Helpers.h"
#include "Vector.h"
#include "DataObject.h"

int populateVectorWithFloats(Vector * vector, int numberOfElements, int isRandom)
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
        vectorPushBack(vector, dataObject);
    }

    return status;
}