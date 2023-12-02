#include <gtest/gtest.h>
#include <stdlib.h>

#include "../include/List/ListNode.h"
#include "../include/DataContainer/DataContainer.h"

void noDisplay(void * data, size_t size)
{

}

class ListNodeTest : public testing::Test
{
protected:
    void SetUp() override
    {
        
    }

    void TearDown() override
    {
        
    }
    
    DataContainer * dataContainer;
    ListNode * listNode;
    
};


TEST_F(ListNodeTest, ListNodeEncapsulationOfDataContainer_nullData)
{
    dataContainer = encapsulateDataOnDataContainer(nullptr, 0, free, noDisplay);
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

    destroyListNode(&listNode);
}


TEST_F(ListNodeTest, ListNodeEncapsulationOfDataContainer_notNullData)
{
    size_t integerArraySize = 3;
    int expectedArrayContent[integerArraySize] = {1,2,1024*1024};

    int * integerArray = (int*) malloc (integerArraySize * sizeof(int));
    
    for(int i = 0; i < integerArraySize; ++i)
    {
        integerArray[i] = expectedArrayContent[i];
    }

    dataContainer = encapsulateDataOnDataContainer(integerArray, integerArraySize, free, noDisplay);
    listNode = encapsulateDataContainerOnListNode(dataContainer);
    DataContainer * retrievedDataContainer = getDataFromListNode(listNode);
    EXPECT_EQ(dataContainer, retrievedDataContainer);

    int * retrievedInternalDataFromDataContainer;
    size_t retrievedInternalDataSizeFromDataContainer;

    getDataOnDataContainer(
        retrievedDataContainer,
        (void**) &retrievedInternalDataFromDataContainer,
        &retrievedInternalDataSizeFromDataContainer);

    EXPECT_EQ(retrievedInternalDataFromDataContainer, integerArray);
    EXPECT_EQ(retrievedInternalDataSizeFromDataContainer, integerArraySize);
    for(int i = 0; i < integerArraySize; ++i)
    {
        EXPECT_EQ(retrievedInternalDataFromDataContainer[i], integerArray[i]);
    }

    destroyListNode(&listNode);
}