#include <gtest/gtest.h>
#include <stdlib.h>

#include "DataObject.h"



void displayIntegerArray(void * integerArray, size_t numberOfElements)
{
    for(int i = 0; i < numberOfElements; ++i)
    {
        printf("%d ", ((int*) integerArray)[i]);
    }
    printf("\n");
}

class DataObjectTest : public testing::Test
{
protected:
    void SetUp() override
    {
        
    }

    void TearDown() override
    {
        // Clean-up code that will be run after each test
        dataObjectDestroy(dataObject);
    }

    // Member variables accessible in the tests
    DataObject *dataObject;
    size_t integerArraySize = 3;
    int expectedArrayContent[3] = {1,2,3};
    int * integerArray;
};

// Test case for data store and retrieval on data object
TEST_F(DataObjectTest, ObjectStoreAndRetrieval)
{
    size_t integerArraySize = 3;
    int expectedArrayContent[3] = {1,2,1024*1024};

    int * integerArray = (int*) malloc (integerArraySize * sizeof(int));
    
    for(int i = 0; i < integerArraySize; ++i)
    {
        integerArray[i] = expectedArrayContent[i];
    }

    dataObject = dataObjectWrapData(integerArray, integerArraySize, free, dataObjectDummyDisplay);

    int * retrievedInternalDataFromDataObject;
    size_t retrievedInternalDataSizeFromDataObject;

    dataObjectGetWrappedData(
        dataObject,
        (void**) &retrievedInternalDataFromDataObject,
        &retrievedInternalDataSizeFromDataObject);

        EXPECT_EQ(retrievedInternalDataFromDataObject, integerArray);
        EXPECT_EQ(retrievedInternalDataSizeFromDataObject, integerArraySize);
        for(int i = 0; i < integerArraySize; ++i)
        {
            EXPECT_EQ(retrievedInternalDataFromDataObject[i], integerArray[i]);
        }
}