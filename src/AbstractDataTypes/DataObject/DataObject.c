#include <stdio.h>
#include <stdlib.h>
#include "DataObject.h"

struct DataObject{
    void * data;
    size_t size;
    void (*dataDestroyCallback)(void *);
    void (*displayCallback)(void *, size_t);
} ;



/*-----------------------------------------------------------------------------------------------*/
DataObject *
createEmptyDataObject()
{
    DataObject * dataObject = malloc(sizeof(DataObject));
    
    dataObject->data = NULL;
    dataObject->size = 0;

    dataObject->dataDestroyCallback = NULL;
    dataObject->displayCallback = NULL;

    return dataObject;
}



/*-----------------------------------------------------------------------------------------------*/
void
setDataOnDataObject(
    DataObject * dataObject,
    void * data,
    size_t size,
    void (*dataDestroyCallback)(void *),
    void (*displayCallback)(void *, size_t))
{    
    dataObject->data = data;
    dataObject->size = size;

    dataObject->dataDestroyCallback = dataDestroyCallback;
    dataObject->displayCallback = displayCallback;
}



/*-----------------------------------------------------------------------------------------------*/
void
getDataOnDataObject(
    DataObject * dataObject,
    void ** data,
    size_t * size)
{
    if(dataObject != NULL)
    {
        *data = dataObject->data;
        *size = dataObject->size;
    }
    else
    {
        *data = NULL;
        *size = (size_t) 0;
    }
}



/*-----------------------------------------------------------------------------------------------*/
/* We assume the DataObject data structure will take the ownership of "void * data" and we can
dealocate "void * data" only by using the clearDataOnDataObject function.
CAUTION: Trying to dealocate "void * data" outside of DataObject functions will result in crash
due to double free. */
DataObject *
encapsulateDataOnDataObject(
    void * data,
    size_t size,
    void (*dataDestroyCallback)(void *),
    void (*displayCallback)(void *, size_t))
{
    DataObject * dataObject = createEmptyDataObject();
    
    setDataOnDataObject(dataObject, data, size, dataDestroyCallback, displayCallback);

    return dataObject;
}



/*-----------------------------------------------------------------------------------------------*/
void
clearDataOnDataObject(DataObject * dataObject)
{
    if (dataObject != NULL)
    {
        if(dataObject->dataDestroyCallback != NULL)
        {
            dataObject->dataDestroyCallback(dataObject->data);
        }

        dataObject->data = NULL;
        dataObject->size = 0;

        dataObject->dataDestroyCallback = NULL;
        dataObject->displayCallback = NULL;
    }
}


/*-----------------------------------------------------------------------------------------------*/
void
displayDataObject(DataObject * dataObject)
{
    if(dataObject != NULL)
    {
        dataObject->displayCallback(dataObject->data, dataObject->size);
    }
}



/*-----------------------------------------------------------------------------------------------*/
void
destroyDataObject(void * dataObject)
{
    clearDataOnDataObject(dataObject);
    free(dataObject);
}



/*-----------------------------------------------------------------------------------------------*/
void
destroyDataObjectKeepingStoredData(void * dataObject)
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
getSizeOfDataObjectInBytes(DataObject * dataObject)
{
    size_t sizeInBytes = 0;

    if(dataObject != NULL)
    {
        sizeInBytes += dataObject->size;
    }

    sizeInBytes += sizeof(DataObject);
    return sizeInBytes;
}
