#include <gtest/gtest.h>
#include <stdlib.h>
#include <stdio.h>

#include "../include/List/List.h"
#include "../include/DataContainer/DataContainer.h"

#include "test_List_Helpers.h"

class ListTest : public testing::Test
{
protected:
    void SetUp() override
    {
        list = createEmptyList();
    }

    void TearDown() override
    {
        destroyList(&list);
    }
    
    List * list;
};


TEST_F(ListTest, createEmptyList)
{
    EXPECT_EQ(countElementsOnList(list), 0);
}

TEST_F(ListTest, insertToFrontOfList)
{
    int repetitions = 10;
    for(int i = 0; i < repetitions; ++i)
    {
        int status = insertToFrontOfList(list, NULL);
        EXPECT_EQ(status, SUCCESS);
    }
    EXPECT_EQ(countElementsOnList(list), repetitions);
}

TEST_F(ListTest, elementAtList_empty)
{
    EXPECT_EQ(elementAtList(list, -1), (DataContainer *) NULL);
    EXPECT_EQ(elementAtList(list, 0), (DataContainer *) NULL);
    EXPECT_EQ(elementAtList(list, 1), (DataContainer *) NULL);
    EXPECT_EQ(elementAtList(list, 10), (DataContainer *) NULL);
}

TEST_F(ListTest, elementAtList_nullList)
{
    EXPECT_EQ(elementAtList(NULL, -1), (DataContainer *) NULL);
    EXPECT_EQ(elementAtList(NULL, 0), (DataContainer *) NULL);
    EXPECT_EQ(elementAtList(NULL, 1), (DataContainer *) NULL);
    EXPECT_EQ(elementAtList(NULL, 10), (DataContainer *) NULL);
}

TEST_F(ListTest, elementAtList_notEmpty)
{
    int numberOfElements = 5;
    size_t size = numberOfElements * sizeof(float*);
    float * data[5];
    for(int i = 0; i < numberOfElements; ++i)
    {
         // DataContainer is responsible for deallocating those floats
        data[i] = (float*) malloc(sizeof(float));

        // Creating the source data as an array: 0.0, 2.0, 4.0, 6.0, 8.0
        *(data[i]) = i*2;
    }
    
    for(int i = 0; i < numberOfElements; ++i)
    {
        DataContainer * dataContainer = encapsulateDataOnDataContainer(
            data[i],
            sizeof(float),
            free,
            testHelper_floatPointerDisplayFunction);

        // Storing the source data
        int status = insertToFrontOfList(list, dataContainer);
        EXPECT_EQ(status, SUCCESS);
    }
    
    EXPECT_EQ(elementAtList(list, -1), (DataContainer *) NULL);
    for(int i = 0; i < numberOfElements; ++i)
    {
        void * dataContainerData;
        size_t dataContainerSize;

        getDataOnDataContainer(elementAtList(list, i), &dataContainerData, &dataContainerSize);
        
        // Verifying against the sequence of values: 4.0, 3.0, 2.0, 1.0, 0.0
        EXPECT_EQ(*(float*) dataContainerData, *(data[numberOfElements - (i + 1)]));
    }

    EXPECT_EQ(elementAtList(list, numberOfElements), (DataContainer *) NULL);
}

TEST_F(ListTest, removeFromFrontOfList)
{
    int inclusions = 10;
    int removals = 4;
    
    for(int i = 0; i < inclusions; ++i)
    {
        int status = insertToFrontOfList(list, NULL);
        EXPECT_EQ(status, SUCCESS);
    }
    
    EXPECT_EQ(countElementsOnList(list), inclusions);
    
    for(int i = 0; i < removals; ++i)
    {
        removeFromFrontOfList(list);
    }

    EXPECT_EQ(countElementsOnList(list), inclusions - removals);

    for(int i = removals; i < inclusions; ++i)
    {
        removeFromFrontOfList(list);
    }

    EXPECT_EQ(countElementsOnList(list), 0);
}

TEST_F(ListTest, popFromFrontOfList)
{
    int numberOfElements = 5;

    populateListWithFloats(list, numberOfElements);

    for(int i = 0; i < numberOfElements; ++i)
    {
        DataContainer * dataContainer = popFromFrontOfList(list);

        EXPECT_EQ(countElementsOnList(list), numberOfElements-(i+1));

        float * retrievedPointerValue;
        size_t retrievedValueSize;

        getDataOnDataContainer(dataContainer, (void**) &retrievedPointerValue, &retrievedValueSize);

        float retrievedValue = *retrievedPointerValue;
        
        // Verifies if List == {4.0, 3.0, 2.0, 1.0, 0.0}
        EXPECT_EQ(retrievedValue, (numberOfElements-i)-1);

        destroyDataContainer(&dataContainer);
    }
}

TEST_F(ListTest, countElementsOnList)
{
    EXPECT_EQ(countElementsOnList(list), 0);
    insertToFrontOfList(list, NULL);
    EXPECT_EQ(countElementsOnList(list), 1);
    insertToFrontOfList(list, NULL);
    EXPECT_EQ(countElementsOnList(list), 2);
    popFromFrontOfList(list);
    EXPECT_EQ(countElementsOnList(list), 1);
    popFromFrontOfList(list);
    EXPECT_EQ(countElementsOnList(list), 0);
}
