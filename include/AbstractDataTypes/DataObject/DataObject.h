#ifndef DATA_OBJECT_H
#define DATA_OBJECT_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>

typedef struct DataObject DataObject;


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
    void (*displayCallback)(void *, size_t));

void
getDataOnDataObject(
    DataObject * dataObject,
    void ** data,
    size_t * size);

void displayDataObject(DataObject * dataObject);

void destroyDataObject(void * dataObject);

void destroyDataObjectKeepingStoredData(void * dataObject);

void dataObjectDummyDisplay(void * data, size_t size);

size_t getSizeOfDataObjectInBytes(DataObject * dataObject);

#ifdef __cplusplus
}
#endif

#endif /* DATA_OBJECT_H */