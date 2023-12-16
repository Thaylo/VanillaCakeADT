#ifndef DATACONTAINER_H
#define DATACONTAINER_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>

typedef struct DataContainer DataContainer;


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
    void (*displayCallback)(void *, size_t));

void
getDataOnDataContainer(
    DataContainer * dataContainer,
    void ** data,
    size_t * size);

void displayDataContainer(DataContainer * dataContainer);

void destroyDataContainer(DataContainer ** dataContainer);

void dataContainerDummyDisplay(void * data, size_t size);

size_t getSizeOfDataContainerInBytes(DataContainer * dataContainer);

#ifdef __cplusplus
}
#endif

#endif /* DATACONTAINER_H */