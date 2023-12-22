#ifndef TEST_LIST_HELPERS_H
#define TEST_LIST_HELPERS_H

#include <iostream>
#include "List.h"
#include "DataObject.h"

int populateListWithFloats(List * list, int numberOfElements, int isRandom);

void testHelper_floatPointerDisplayFunction(void * data, size_t size);

int compareFloats(DataObject * dataObject1, DataObject * dataObject2, int usingAscendingOrder);

#endif /* TEST_LIST_HELPERS_H */