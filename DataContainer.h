#ifndef DATACONTAINER_H
#define DATACONTAINER_H

#include <stdlib.h>

typedef struct DataContainer DataContainer;

DataContainer * createEmptyDataContainer();

void setDataOnDataContainer(
    DataContainer * dataContainer,
    void * data,
    size_t size,
    void (*dataDestroyCallback)(void *),
    void (*displayCallback)(void *, size_t));

void
getDataOnDataContainer(
    DataContainer * dataContainer,
    void ** data,
    size_t * size);

DataContainer *
encapsulateDataOnDataContainer(
    void * data,
    size_t size,
    void (*dataDestroyCallback)(void *),
    void (*displayCallback)(void *, size_t));

void displayDataContainer(DataContainer * dataContainer);

void clearDataOnDataContainer(DataContainer * dataContainer);

DataContainer * destroyDataContainer(DataContainer * dataContainer);

#endif /* DATACONTAINER_H */