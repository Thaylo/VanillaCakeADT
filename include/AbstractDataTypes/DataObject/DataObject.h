#ifndef DATA_OBJECT_H
#define DATA_OBJECT_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>

typedef struct DataObject DataObject;


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
    void (*displayCallback)(void *, size_t));

DataObject **
dataObjectCreatePointerArray(int arrayLength);

void
dataObjectGetWrappedData(
    DataObject * dataObject,
    void ** wrappedData,
    size_t * size);

void dataObjectDisplay(DataObject * dataObject);

void dataObjectDestroy(void * dataObject);

void dataObjectDestroyKeepingWrappedData(void * dataObject);

void dataObjectDummyDisplay(void * data, size_t size);

size_t dataObjectGetSizeInBytes(DataObject * dataObject);

void dataObjectDestroyPointerArray(DataObject ** dataObjectArray, int arrayLength);

#ifdef __cplusplus
}
#endif

#endif /* DATA_OBJECT_H */