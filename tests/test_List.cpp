#include <gtest/gtest.h>
#include <stdlib.h>
#include <stdio.h>

#include "../include/List/List.h"
#include "../include/DataContainer/DataContainer.h"

void testHelper_floatPointerDisplayFunction(void * data, size_t size)
{
    printf("%f ", *(float*) data);
}

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


TEST_F(ListTest, createEmptyList_test)
{
    EXPECT_EQ(countElementsOnList(list), 0);
}

TEST_F(ListTest, insertToFrontOfList_test)
{   
    int repetitions = 10;
    for(int i = 0; i < repetitions; ++i)
    {
        int status = insertToFrontOfList(list, NULL);
        EXPECT_EQ(status, SUCCESS);
    }
    EXPECT_EQ(countElementsOnList(list), repetitions);
}

TEST_F(ListTest, removeFromFrontOfList_test)
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

    for(int i = 0; i < inclusions - removals; ++i)
    {
        removeFromFrontOfList(list);
    }

    EXPECT_EQ(countElementsOnList(list), 0);
}

TEST_F(ListTest, insertToFrontOfList_ordering_and_popFromFrontOfList_test)
{   
    int numberOfElements = 5;
    size_t size = numberOfElements * sizeof(float*);
    float * data[5];
    for(int i = 0; i < numberOfElements; ++i)
    {
         // DataContainer is responsible for deallocating those floats
        data[i] = (float*) malloc(sizeof(float));

        // Creating the source data as an array: 0.0, 1.0, 2.0, 3.0, 4.0
        *(data[i]) = i;
    }
    
    for(int i = 0; i < numberOfElements; ++i)
    {
        DataContainer * dataContainer = encapsulateDataOnDataContainer(
            data[i],
            sizeof(float),
            free,
            testHelper_floatPointerDisplayFunction);

        // Creating the sequence of values: 4.0, 3.0, 2.0, 1.0, 0.0
        int status = insertToFrontOfList(list, dataContainer);
        EXPECT_EQ(status, SUCCESS);
    }

    EXPECT_EQ(countElementsOnList(list), numberOfElements);
    
    // To print the actual sequence, uncomment the 2 lines below. 
    // displayList(list); // Expected sequence of values: 4.0, 3.0, 2.0, 1.0, 0.0
    // printf("\n");

    for(int i = 0; i < numberOfElements; ++i)
    {
        DataContainer * dataContainer = popFromFrontOfList(list);

        EXPECT_EQ(countElementsOnList(list), numberOfElements-(i+1));

        float * retrievedValuePointer;
        size_t retrievedValueSize;

        getDataOnDataContainer(dataContainer, (void**) &retrievedValuePointer, &retrievedValueSize);

        // Verifies the expected sequence of values: 4.0, 3.0, 2.0, 1.0, 0.0
        EXPECT_EQ(*retrievedValuePointer, (numberOfElements-i)-1);
    }

}