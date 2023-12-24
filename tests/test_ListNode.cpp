#include <gtest/gtest.h>
#include <stdlib.h>

#include "ListNode.h"
#include "DataObject.h"

class ListNodeTest : public testing::Test
{
protected:
    void SetUp() override
    {
        
    }

    void TearDown() override
    {
        listNodeDestroy(listNode);
    }
    
    DataObject * dataObject;
    ListNode * listNode;
};


TEST_F(ListNodeTest, ListNodeEncapsulationOfDataObject_nullData)
{
    dataObject = dataObjectWrapData(nullptr, 0, free, dataObjectDummyDisplay);
    listNode = listNodeWrapDataObject(dataObject);
    DataObject * retrievedDataObject = listNodeGetDataObject(listNode);
    EXPECT_EQ(dataObject, retrievedDataObject);

    void * retrievedInternalDataFromDataObject;
    size_t retrievedInternalDataSizeFromDataObject;

    dataObjectGetWrappedData(
        retrievedDataObject,
        &retrievedInternalDataFromDataObject,
        &retrievedInternalDataSizeFromDataObject);

    EXPECT_EQ(retrievedInternalDataFromDataObject, nullptr);
    EXPECT_EQ(retrievedInternalDataSizeFromDataObject, 0);
}


TEST_F(ListNodeTest, ListNodeEncapsulationOfDataObject_notNullData)
{
    size_t integerArraySize = 3;
    int expectedArrayContent[3] = {1,2,1024*1024};

    int * integerArray = (int*) malloc (integerArraySize * sizeof(int));
    
    for(int i = 0; i < integerArraySize; ++i)
    {
        integerArray[i] = expectedArrayContent[i];
    }

    dataObject = dataObjectWrapData(integerArray, integerArraySize, free, dataObjectDummyDisplay);
    listNode = listNodeWrapDataObject(dataObject);
    DataObject * retrievedDataObject = listNodeGetDataObject(listNode);
    EXPECT_EQ(dataObject, retrievedDataObject);
}