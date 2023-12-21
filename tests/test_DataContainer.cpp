#include <gtest/gtest.h>
#include <stdlib.h>

#include "DataContainer.h"



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
    int * integerArray;
};

// Test case for data store and retrieval on data container
TEST_F(DataContainerTest, ContainerStoreAndRetrieval)
{
    size_t integerArraySize = 3;
    int expectedArrayContent[3] = {1,2,1024*1024};

    int * integerArray = (int*) malloc (integerArraySize * sizeof(int));
    
    for(int i = 0; i < integerArraySize; ++i)
    {
        integerArray[i] = expectedArrayContent[i];
    }

    dataContainer = encapsulateDataOnDataContainer(integerArray, integerArraySize, free, dataContainerDummyDisplay);

    int * retrievedInternalDataFromDataContainer;
    size_t retrievedInternalDataSizeFromDataContainer;

    getDataOnDataContainer(
        dataContainer,
        (void**) &retrievedInternalDataFromDataContainer,
        &retrievedInternalDataSizeFromDataContainer);

        EXPECT_EQ(retrievedInternalDataFromDataContainer, integerArray);
        EXPECT_EQ(retrievedInternalDataSizeFromDataContainer, integerArraySize);
        for(int i = 0; i < integerArraySize; ++i)
        {
            EXPECT_EQ(retrievedInternalDataFromDataContainer[i], integerArray[i]);
        }
}