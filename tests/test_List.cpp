#include <gtest/gtest.h>
#include <stdlib.h>
#include <stdio.h>

#include "../include/List/List.h"
#include "../include/DataContainer/DataContainer.h"

#include "test_List_Helpers.h"
#ifdef _WIN32
#include <sys/timeb.h>
#else
#include <sys/time.h>
#endif

class ListTest : public testing::Test
{
protected:
    void SetUp() override
    {
        list = createEmptyList();
        srand(time(NULL));   // Initialization, should only be called once.
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
    populateListWithFloats(list, numberOfElements, 0);
    
    EXPECT_EQ(elementAtList(list, -1), (DataContainer *) NULL);
    for(int i = 0; i < numberOfElements; ++i)
    {
        void * dataContainerData;
        size_t dataContainerSize;

        getDataOnDataContainer(elementAtList(list, i), &dataContainerData, &dataContainerSize);
        
        // Verifying against the sequence of values: 4.0, 3.0, 2.0, 1.0, 0.0
        EXPECT_EQ(*(float*) dataContainerData, numberOfElements - (i + 1));
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

    populateListWithFloats(list, numberOfElements, 0);

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

TEST_F(ListTest, sortList)
{
    struct timeb start, end;
    int diff;
    int numberOfElements = 5;
    
    int i = 0;
    int status = populateListWithFloats(list, numberOfElements, 1);
    int isSorted;

    if(status != SUCCESS)
    {
        printf("populateListWithFloatsDecreasing failed \n");
        return;
    }

    //std::cout << "Original List values:" << std::endl;
    //displayList(list);

    sortList(list, compareFloats, 1);
    //std::cout << "List values increasing:" << std::endl;
    //displayList(list);
    isSorted = isListSorted(list, compareFloats, 1);
    EXPECT_EQ(isSorted, 1);

    sortList(list, compareFloats, 0);
    //std::cout << "List values decreasing:" << std::endl;
    //displayList(list);
    isSorted = isListSorted(list, compareFloats, 0);
    EXPECT_EQ(isSorted, 1);
}

TEST_F(ListTest, sortList_StressTest)
{
    return; // TODO Remove this return statement line to experiment with this test.

    struct timeb start, end;
    int diff;
    int stressFactor = 42709;
    for(int numberOfElements = stressFactor; numberOfElements < stressFactor+1; numberOfElements += 1)
    {
        int i = 0;
        int status = populateListWithFloats(list, numberOfElements, 1);
        int isSorted;

        if(status != SUCCESS)
        {
            std::cout << "populateListWithFloatsDecreasing failed \n" << std::endl;
            return;
        }

        std::cout << "Original List values:" << std::endl;
        displayList(list);

        std::cout << "Starting to sort..." << std::endl;
        ftime(&start);
        sortList(list, compareFloats, 1);
        ftime(&end);
        std::cout << "Sorting finished." << std::endl;

        diff = (int) (1000.0 * (end.time - start.time) + (end.millitm - start.millitm));
        size_t listSizeInBytes = getListSizeInBytes(list);
        std::cout << "List size during STRESS TEST: " <<  listSizeInBytes/((float)1024*1024) << "[MB], time to sort:" << diff << " [ms]" << std::endl;
        std::cout << std::endl;

        std::cout << "List values increasing:" << std::endl;
        displayList(list);
        isSorted = isListSorted(list, compareFloats, 1);
        EXPECT_EQ(isSorted, 1);

        sortList(list, compareFloats, 0);

        std::cout << "List values decreasing:" << std::endl;
        displayList(list);
        isSorted = isListSorted(list, compareFloats, 0);
        EXPECT_EQ(isSorted, 1);

        if(list == NULL)
        {
            std::cout << "createEmptyList failed during STRESS TEST\n" << std::endl;
            return;
        }

        destroyList(&list);
        list = createEmptyList();
    }
}
