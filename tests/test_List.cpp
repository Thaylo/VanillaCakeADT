#include <gtest/gtest.h>
#include <stdlib.h>
#include <stdio.h>

#include "../include/List/List.h"
#include "../include/DataContainer/DataContainer.h"

#include "test_List_Helpers.h"

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
#include <sys/timeb.h>
#elif __APPLE__
#include <sys/timeb.h>
#elif __linux__
#include <time.h>
#else
#   error "Unknown compiler"
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
    
    sortList(list, compareFloats, 1);
    
    isSorted = isListSorted(list, compareFloats, 1);
    EXPECT_EQ(isSorted, 1);

    sortList(list, compareFloats, 0);
    
    isSorted = isListSorted(list, compareFloats, 0);
    EXPECT_EQ(isSorted, 1);
}

TEST_F(ListTest, sortList_StressTest)
{

#if defined(__linux__)
    timespec start, end;
#else
    struct timeb start, end;
#endif
    
    int diff;
    int numberOfElements = 20000;

    int i = 0;
    int status = populateListWithFloats(list, numberOfElements, 1);
    int isSorted;

    if(status != SUCCESS)
    {
        EXPECT_EQ(status, SUCCESS);
        std::cout << "populateListWithFloatsDecreasing failed \n" << std::endl;
        return;
    }

    std::cout << "Original List values:" << std::endl;
    displayList(list);

    std::cout << "Starting to sort..." << std::endl;
    #if defined(__linux__)
        clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &start);
    #else
        ftime(&start);
    #endif
    
    sortList(list, compareFloats, 1);
    

    #if defined(__linux__)
        clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &end);
    #else
        ftime(&end);
    #endif

    std::cout << "Sorting finished." << std::endl;

    

    #if defined(__linux__)
        diff = (end.tv_sec - start.tv_sec) * 1e3 + (end.tv_nsec - start.tv_nsec) / 1e6;    // in milliseconds
    #else
        diff = (int) (1000.0 * (end.time - start.time) + (end.millitm - start.millitm));
    #endif


    size_t listSizeInBytes = getListSizeInBytes(list);
    std::cout << "List size during STRESS TEST: " <<  listSizeInBytes/((float)1024*1024) << "[MB], time to sort: " << diff << " [ms]" << std::endl;
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