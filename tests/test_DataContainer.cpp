#include <gtest/gtest.h>
#include <stdlib.h>

#include "../include/DataContainer/DataContainer.h"

void displayIntegerArray(void * integerArray, size_t numberOfElements)
{
    for(int i = 0; i < numberOfElements; ++i)
    {
        printf("%d ", ((int*) integerArray)[i]);
    }
    printf("\n");
}

class DataContainerTest : public testing::Test
{
protected:
    void SetUp() override
    {
        
        int * integerArray = (int*) malloc (integerArraySize * sizeof(int));
        for(int i = 0; i < integerArraySize; ++i)
        {
            integerArray[i] = expectedArrayContent[i];
        }

        // Initialization code that will be run before each test
        dataContainer = encapsulateDataOnDataContainer(
            integerArray,
            integerArraySize,
            free,
            displayIntegerArray
        );
    }

    void TearDown() override
    {
        // Clean-up code that will be run after each test
        destroyDataContainer(&dataContainer);
    }

    // Member variables accessible in the tests
    DataContainer *dataContainer;
    size_t integerArraySize = 3;
    int expectedArrayContent[3] = {1,2,3};
};

// Test case for data store and retrieval on data container
TEST_F(DataContainerTest, ContainerStoreAndRetrieval)
{
    int *retrievedTestContent = (int*) getDataPointerForTesting(dataContainer);
    
    for(int i = 0; i < integerArraySize; ++i)
    {
        EXPECT_EQ(retrievedTestContent[i], expectedArrayContent[i]);
    }
}