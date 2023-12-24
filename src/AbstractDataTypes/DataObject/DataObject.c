#include <stdio.h>
#include <stdlib.h>
#include "DataObject.h"

struct DataObject{
    void * wrappedData;
    size_t size;
    void (*dataDestroyCallback)(void *);
    void (*displayCallback)(void *, size_t);
} ;



/*-----------------------------------------------------------------------------------------------*/
DataObject *
createEmptyDataObject()
{
    DataObject * dataObject = malloc(sizeof(DataObject));
    
    dataObject->wrappedData = NULL;
    dataObject->size = 0;

    dataObject->dataDestroyCallback = NULL;
    dataObject->displayCallback = NULL;

    return dataObject;
}



/*-----------------------------------------------------------------------------------------------*/
void
setDataOnDataObject(
    DataObject * dataObject,
    void * wrappedData,
    size_t size,
    void (*dataDestroyCallback)(void *),
    void (*displayCallback)(void *, size_t))
{    
    dataObject->wrappedData = wrappedData;
    dataObject->size = size;

    dataObject->dataDestroyCallback = dataDestroyCallback;
    dataObject->displayCallback = displayCallback;
}



/*-----------------------------------------------------------------------------------------------*/
void
dataObjectGetWrappedData(
    DataObject * dataObject,
    void ** wrappedData,
    size_t * size)
{
    if(dataObject != NULL)
    {
        *wrappedData = dataObject->wrappedData;
        *size = dataObject->size;
    }
    else
    {
        *wrappedData = NULL;
        *size = (size_t) 0;
    }
}



/*-----------------------------------------------------------------------------------------------*/
/* We assume the DataObject data structure will take the ownership of "void * wrappedData" and we can
dealocate "void * wrappedData" only by using the clearDataOnDataObject function.
CAUTION: Trying to dealocate "void * wrappedData" outside of DataObject functions will result in crash
due to double free. */
DataObject *
dataObjectWrapData(
    void * wrappedData,
    size_t size,
    void (*dataDestroyCallback)(void *),
    void (*displayCallback)(void *, size_t))
{
    DataObject * dataObject = createEmptyDataObject();
    
    setDataOnDataObject(dataObject, wrappedData, size, dataDestroyCallback, displayCallback);

    return dataObject;
}



/*-----------------------------------------------------------------------------------------------*/
DataObject **
dataObjectCreatePointerArray(int arrayLength)
{
    DataObject ** dataObjectArray = malloc(arrayLength * sizeof(DataObject*));

    for(int i = 0; i < arrayLength; i++)
    {
        dataObjectArray[i] = createEmptyDataObject();
    }

    return dataObjectArray;
}



/*-----------------------------------------------------------------------------------------------*/
void
clearDataOnDataObject(DataObject * dataObject)
{
    if (dataObject != NULL)
    {
        if(dataObject->dataDestroyCallback != NULL)
        {
            dataObject->dataDestroyCallback(dataObject->wrappedData);
        }

        dataObject->wrappedData = NULL;
        dataObject->size = 0;

        dataObject->dataDestroyCallback = NULL;
        dataObject->displayCallback = NULL;
    }
}


/*-----------------------------------------------------------------------------------------------*/
void
dataObjectDisplay(DataObject * dataObject)
{
    if(dataObject != NULL)
    {
        dataObject->displayCallback(dataObject->wrappedData, dataObject->size);
    }
}



/*-----------------------------------------------------------------------------------------------*/
void
dataObjectDestroy(void * dataObject)
{
    clearDataOnDataObject(dataObject);
    free(dataObject);
}



/*-----------------------------------------------------------------------------------------------*/
void
dataObjectDestroyKeepingWrappedData(void * dataObject)
{
    free(dataObject);
}



/*-----------------------------------------------------------------------------------------------*/
void
dataObjectDummyDisplay(void * data, size_t size)
{

}



/*-----------------------------------------------------------------------------------------------*/
size_t
dataObjectGetSizeInBytes(DataObject * dataObject)
{
    size_t sizeInBytes = 0;

    if(dataObject != NULL)
    {
        sizeInBytes += dataObject->size;
    }

    sizeInBytes += sizeof(DataObject);
    return sizeInBytes;
}



/*-----------------------------------------------------------------------------------------------*/
void
dataObjectDestroyPointerArray(DataObject ** dataObjectArray, int arrayLength)
{
    
    for(int i = 0; i < arrayLength; i++)
    {
        dataObjectDestroy(dataObjectArray[i]);
    }

    free(dataObjectArray);
}