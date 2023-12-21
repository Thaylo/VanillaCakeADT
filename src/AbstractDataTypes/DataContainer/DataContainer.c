#include <stdio.h>
#include <stdlib.h>
#include "DataContainer.h"

struct DataContainer{
    void * data;
    size_t size;
    void (*dataDestroyCallback)(void *);
    void (*displayCallback)(void *, size_t);
} ;



/*-----------------------------------------------------------------------------------------------*/
DataContainer *
createEmptyDataContainer()
{
    DataContainer * dataContainer = malloc(sizeof(DataContainer));
    
    dataContainer->data = NULL;
    dataContainer->size = 0;

    dataContainer->dataDestroyCallback = NULL;
    dataContainer->displayCallback = NULL;

    return dataContainer;
}



/*-----------------------------------------------------------------------------------------------*/
void
setDataOnDataContainer(
    DataContainer * dataContainer,
    void * data,
    size_t size,
    void (*dataDestroyCallback)(void *),
    void (*displayCallback)(void *, size_t))
{    
    dataContainer->data = data;
    dataContainer->size = size;

    dataContainer->dataDestroyCallback = dataDestroyCallback;
    dataContainer->displayCallback = displayCallback;
}



/*-----------------------------------------------------------------------------------------------*/
void
getDataOnDataContainer(
    DataContainer * dataContainer,
    void ** data,
    size_t * size)
{
    if(dataContainer != NULL)
    {
        *data = dataContainer->data;
        *size = dataContainer->size;
    }
    else
    {
        *data = NULL;
        *size = (size_t) 0;
    }
}



/*-----------------------------------------------------------------------------------------------*/
/* We assume the DataContainer data structure will take the ownership of "void * data" and we can
dealocate "void * data" only by using the clearDataOnDataContainer function.
CAUTION: Trying to dealocate "void * data" outside of DataContainer functions will result in crash
due to double free. */
DataContainer *
encapsulateDataOnDataContainer(
    void * data,
    size_t size,
    void (*dataDestroyCallback)(void *),
    void (*displayCallback)(void *, size_t))
{
    DataContainer * dataContainer = createEmptyDataContainer();
    
    setDataOnDataContainer(dataContainer, data, size, dataDestroyCallback, displayCallback);

    return dataContainer;
}



/*-----------------------------------------------------------------------------------------------*/
void
clearDataOnDataContainer(DataContainer * dataContainer)
{
    if (dataContainer != NULL)
    {
        if(dataContainer->dataDestroyCallback != NULL)
        {
            dataContainer->dataDestroyCallback(dataContainer->data);
        }

        dataContainer->data = NULL;
        dataContainer->size = 0;

        dataContainer->dataDestroyCallback = NULL;
        dataContainer->displayCallback = NULL;
    }
}


/*-----------------------------------------------------------------------------------------------*/
void
displayDataContainer(DataContainer * dataContainer)
{
    if(dataContainer != NULL)
    {
        dataContainer->displayCallback(dataContainer->data, dataContainer->size);
    }
}



/*-----------------------------------------------------------------------------------------------*/
void
destroyDataContainer(DataContainer ** dataContainer)
{
    clearDataOnDataContainer(*dataContainer);

    if(*dataContainer != NULL)
    {
        free(*dataContainer);
    }
    
    *dataContainer = NULL;
}



/*-----------------------------------------------------------------------------------------------*/
void dataContainerDummyDisplay(void * data, size_t size)
{

}

/*-----------------------------------------------------------------------------------------------*/
size_t getSizeOfDataContainerInBytes(DataContainer * dataContainer)
{
    size_t sizeInBytes = 0;

    if(dataContainer != NULL)
    {
        sizeInBytes += dataContainer->size;
    }

    sizeInBytes += sizeof(DataContainer);
    return sizeInBytes;
}
