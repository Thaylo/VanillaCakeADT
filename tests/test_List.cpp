#include <gtest/gtest.h>
#include <stdlib.h>
#include <stdio.h>

#include "List.h"
#include "DataContainer.h"

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
        destroyList(list);
    }
    
    List * list;
    int numberOfListElementsDuringStressTest = 1*1000*1000;
};

TEST_F(ListTest, createEmptyList)
{
    EXPECT_EQ(getListLength(list), 0);
}

TEST_F(ListTest, insertToFrontOfList)
{
    int repetitions = 11;
    for(int i = 0; i < repetitions; ++i)
    {
        int status = insertToFrontOfList(list, NULL);
        EXPECT_EQ(status, SUCCESS);
    }
    EXPECT_EQ(getListLength(list), repetitions);
}

TEST_F(ListTest, elementAtList_empty)
{
    EXPECT_EQ(elementAtListIndex(list, -1), (DataContainer *) NULL);
    EXPECT_EQ(elementAtListIndex(list, 0), (DataContainer *) NULL);
    EXPECT_EQ(elementAtListIndex(list, 1), (DataContainer *) NULL);
    EXPECT_EQ(elementAtListIndex(list, 10), (DataContainer *) NULL);
}

TEST_F(ListTest, elementAtList_nullList)
{
    EXPECT_EQ(elementAtListIndex(NULL, -1), (DataContainer *) NULL);
    EXPECT_EQ(elementAtListIndex(NULL, 0), (DataContainer *) NULL);
    EXPECT_EQ(elementAtListIndex(NULL, 1), (DataContainer *) NULL);
    EXPECT_EQ(elementAtListIndex(NULL, 10), (DataContainer *) NULL);
}

TEST_F(ListTest, elementAtList_notEmpty)
{
    int numberOfElements = 5;
    populateListWithFloats(list, numberOfElements, 0);
    
    EXPECT_EQ(elementAtListIndex(list, -1), (DataContainer *) NULL);
    for(int i = 0; i < numberOfElements; ++i)
    {
        void * dataContainerData;
        size_t dataContainerSize;

        getDataOnDataContainer(elementAtListIndex(list, i), &dataContainerData, &dataContainerSize);
        
        // Verifying against the sequence of values: 4.0, 3.0, 2.0, 1.0, 0.0
        EXPECT_EQ(*(float*) dataContainerData, numberOfElements - (i + 1));
    }

    EXPECT_EQ(elementAtListIndex(list, numberOfElements), (DataContainer *) NULL);
}

TEST_F(ListTest, removeFromFrontOfList)
{
    int inclusions = 11;
    int removals = 4;
    
    for(int i = 0; i < inclusions; ++i)
    {
        int status = insertToFrontOfList(list, NULL);
        EXPECT_EQ(status, SUCCESS);
    }
    
    EXPECT_EQ(getListLength(list), inclusions);
    
    for(int i = 0; i < removals; ++i)
    {
        removeFromFrontOfList(list);
    }

    EXPECT_EQ(getListLength(list), inclusions - removals);

    for(int i = removals; i < inclusions; ++i)
    {
        removeFromFrontOfList(list);
    }

    EXPECT_EQ(getListLength(list), 0);
}

TEST_F(ListTest, popFromFrontOfList)
{
    int numberOfElements = 5;

    populateListWithFloats(list, numberOfElements, 0);

    for(int i = 0; i < numberOfElements; ++i)
    {
        DataContainer * dataContainer = popFromFrontOfList(list);

        EXPECT_EQ(getListLength(list), numberOfElements-(i+1));

        float * retrievedPointerValue;
        size_t retrievedValueSize;

        getDataOnDataContainer(dataContainer, (void**) &retrievedPointerValue, &retrievedValueSize);

        float retrievedValue = *retrievedPointerValue;
        
        // Verifies if List == {4.0, 3.0, 2.0, 1.0, 0.0}
        EXPECT_EQ(retrievedValue, (numberOfElements-i)-1);

        destroyDataContainer(dataContainer);
    }
}

TEST_F(ListTest, getListLength)
{
    EXPECT_EQ(getListLength(list), 0);
    insertToFrontOfList(list, NULL);
    EXPECT_EQ(getListLength(list), 1);
    insertToFrontOfList(list, NULL);
    EXPECT_EQ(getListLength(list), 2);
    popFromFrontOfList(list);
    EXPECT_EQ(getListLength(list), 1);
    popFromFrontOfList(list);
    EXPECT_EQ(getListLength(list), 0);
}

TEST_F(ListTest, sortList)
{
    int diff;
    int numberOfElements = 5;
    
    int i = 0;
    int status = populateListWithFloats(list, numberOfElements, 0);
    int isSorted;

    if(status != SUCCESS)
    {
        printf("populateListWithFloatsDecreasing failed \n");
        return;
    }
    displayList(list); printf("\n\n");

    sortList(&list, compareFloats, 1);
    isSorted = verifyIfListIsSorted(list, compareFloats, 1);
    EXPECT_EQ(isSorted, 1);

    sortList(&list, compareFloats, 0);
    isSorted = verifyIfListIsSorted(list, compareFloats, 0);
    EXPECT_EQ(isSorted, 1);
}

TEST_F(ListTest, sortList_ascendingOrder_StressTest)
{
#if defined(__linux__)
    timespec start, end;
#else
    struct timeb start, end;
#endif
    
    int diff;

    int i = 0;
    std::cout << "Starting to populate list..." << std::endl;
    int status = populateListWithFloats(list, numberOfListElementsDuringStressTest, 1);
    std::cout << "Finished populating list." << std::endl;
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
    
    sortList(&list, compareFloats, 1);
    
    #if defined(__linux__)
        clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &end);
    #else
        ftime(&end);
    #endif


    #if defined(__linux__)
        diff = (end.tv_sec - start.tv_sec) * 1e3 + (end.tv_nsec - start.tv_nsec) / 1e6;    // in milliseconds
    #else
        diff = (int) (1000.0 * (end.time - start.time) + (end.millitm - start.millitm));
    #endif

    size_t listSizeInBytes = getListSizeInBytes(list);
    // std::cout << "List size during STRESS TEST: " <<  listSizeInBytes/((float)1024*1024) << "[MB], time to sort: " << diff << " [ms]" << std::endl;
    std::cout << "Sorting finished." << std::endl;
    std::cout << "List values ascending:" << std::endl;
    displayList(list);
    isSorted = verifyIfListIsSorted(list, compareFloats, 1);
    EXPECT_EQ(isSorted, 1);
}

TEST_F(ListTest, splitListInTwoHalves)
{
    int numberOfElements = 5;
    int status = populateListWithFloats(list, numberOfElements, 0);
    if(status != SUCCESS)
    {
        EXPECT_EQ(status, SUCCESS);
        std::cout << "populateListWithFloatsDecreasing failed \n" << std::endl;
        return;
    }

    List * firstHalf = NULL;
    List * secondHalf = NULL;

    splitListInTwoHalves(&list, &firstHalf, &secondHalf);

    EXPECT_EQ(getListLength(firstHalf), 3);
    EXPECT_EQ(getListLength(firstHalf), getListLengthByCounting(firstHalf));
    EXPECT_EQ(getListLength(secondHalf), 2);
    EXPECT_EQ(getListLength(secondHalf), getListLengthByCounting(secondHalf));

    destroyList(firstHalf);
    destroyList(secondHalf);
}



TEST_F(ListTest, sortList_descendingOrder_StressTest)
{
#if defined(__linux__)
    timespec start, end;
#else
    struct timeb start, end;
#endif
    
    int diff;
    
    int i = 0;
    int status = populateListWithFloats(list, numberOfListElementsDuringStressTest, 1);
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
    
    sortList(&list, compareFloats, 0);
    
    #if defined(__linux__)
        clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &end);
    #else
        ftime(&end);
    #endif

    #if defined(__linux__)
        diff = (end.tv_sec - start.tv_sec) * 1e3 + (end.tv_nsec - start.tv_nsec) / 1e6;    // in milliseconds
    #else
        diff = (int) (1000.0 * (end.time - start.time) + (end.millitm - start.millitm));
    #endif

    size_t listSizeInBytes = getListSizeInBytes(list);
    // std::cout << "List size during STRESS TEST: " <<  listSizeInBytes/((float)1024*1024) << "[MB], time to sort: " << diff << " [ms]" << std::endl;
    std::cout << "Sorting finished." << std::endl;
    std::cout << "List values descending:" << std::endl;
    displayList(list);
    isSorted = verifyIfListIsSorted(list, compareFloats, 0);
    EXPECT_EQ(isSorted, 1);
}