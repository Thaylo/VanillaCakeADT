#include <gtest/gtest.h>
#include <stdlib.h>

#include "ListNode.h"
#include "DataContainer.h"

class ListNodeTest : public testing::Test
{
protected:
    void SetUp() override
    {
        
    }

    void TearDown() override
    {
        destroyListNode(&listNode);
    }
    
    DataContainer * dataContainer;
    ListNode * listNode;
};


TEST_F(ListNodeTest, ListNodeEncapsulationOfDataContainer_nullData)
{
    dataContainer = encapsulateDataOnDataContainer(nullptr, 0, free, dataContainerDummyDisplay);
    listNode = encapsulateDataContainerOnListNode(dataContainer);
    DataContainer * retrievedDataContainer = getDataFromListNode(listNode);
    EXPECT_EQ(dataContainer, retrievedDataContainer);

    void * retrievedInternalDataFromDataContainer;
    size_t retrievedInternalDataSizeFromDataContainer;

    getDataOnDataContainer(
        retrievedDataContainer,
        &retrievedInternalDataFromDataContainer,
        &retrievedInternalDataSizeFromDataContainer);

    EXPECT_EQ(retrievedInternalDataFromDataContainer, nullptr);
    EXPECT_EQ(retrievedInternalDataSizeFromDataContainer, 0);
}


TEST_F(ListNodeTest, ListNodeEncapsulationOfDataContainer_notNullData)
{
    size_t integerArraySize = 3;
    int expectedArrayContent[3] = {1,2,1024*1024};

    int * integerArray = (int*) malloc (integerArraySize * sizeof(int));
    
    for(int i = 0; i < integerArraySize; ++i)
    {
        integerArray[i] = expectedArrayContent[i];
    }

    dataContainer = encapsulateDataOnDataContainer(integerArray, integerArraySize, free, dataContainerDummyDisplay);
    listNode = encapsulateDataContainerOnListNode(dataContainer);
    DataContainer * retrievedDataContainer = getDataFromListNode(listNode);
    EXPECT_EQ(dataContainer, retrievedDataContainer);
}