#ifndef TEST_GENERAL_HELPERS_H
#define TEST_GENERAL_HELPERS_H

#include <iostream>
#include "DataObject.h"

void testHelper_floatPointerDisplayFunction(void * data, size_t size);

int compareFloats(DataObject * dataObject1, DataObject * dataObject2, int usingAscendingOrder);

#endif /* TEST_GENERAL_HELPERS_H */