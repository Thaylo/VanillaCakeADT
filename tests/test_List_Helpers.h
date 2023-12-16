#ifndef TEST_LIST_HELPERS_H
#define TEST_LIST_HELPERS_H

#include <iostream>
#include "../include/List/List.h"
#include "../include/DataContainer/DataContainer.h"

int populateListWithFloats(List * list, int numberOfElements, int isRandom);

void testHelper_floatPointerDisplayFunction(void * data, size_t size);

int compareFloats(DataContainer * dataContainer1, DataContainer * dataContainer2, int usingAscendingOrder);

#endif /* TEST_LIST_HELPERS_H */