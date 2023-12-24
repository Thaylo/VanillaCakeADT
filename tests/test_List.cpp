#include <gtest/gtest.h>
#include <stdlib.h>
#include <stdio.h>

#include "List.h"
#include "DataObject.h"

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
        list = listCreate();
        srand(time(NULL));   // Initialization, should only be called once.
    }

    void TearDown() override
    {
        listDestroy(list);
    }
    
    List * list;
    int numberOfListElementsDuringStressTest = 1*1000;
};

TEST_F(ListTest, listCreate)
{
    EXPECT_EQ(listGetLength(list), 0);
}

TEST_F(ListTest, listInsertToFrontOf)
{
    int repetitions = 11;
    for(int i = 0; i < repetitions; ++i)
    {
        int status = listInsertToFrontOf(list, NULL);
        EXPECT_EQ(status, SUCCESS);
    }
    EXPECT_EQ(listGetLength(list), repetitions);
}

TEST_F(ListTest, elementAtList_empty)
{
    EXPECT_EQ(listElementAtIndexPosition(list, -1), (DataObject *) NULL);
    EXPECT_EQ(listElementAtIndexPosition(list, 0), (DataObject *) NULL);
    EXPECT_EQ(listElementAtIndexPosition(list, 1), (DataObject *) NULL);
    EXPECT_EQ(listElementAtIndexPosition(list, 10), (DataObject *) NULL);
}

TEST_F(ListTest, elementAtList_nullList)
{
    EXPECT_EQ(listElementAtIndexPosition(NULL, -1), (DataObject *) NULL);
    EXPECT_EQ(listElementAtIndexPosition(NULL, 0), (DataObject *) NULL);
    EXPECT_EQ(listElementAtIndexPosition(NULL, 1), (DataObject *) NULL);
    EXPECT_EQ(listElementAtIndexPosition(NULL, 10), (DataObject *) NULL);
}

TEST_F(ListTest, elementAtList_notEmpty)
{
    int numberOfElements = 5;
    populateListWithFloats(list, numberOfElements, 0);
    
    EXPECT_EQ(listElementAtIndexPosition(list, -1), (DataObject *) NULL);
    for(int i = 0; i < numberOfElements; ++i)
    {
        void * dataObjectData;
        size_t dataObjectSize;

        dataObjectGetWrappedData(listElementAtIndexPosition(list, i), &dataObjectData, &dataObjectSize);
        
        // Verifying against the sequence of values: 4.0, 3.0, 2.0, 1.0, 0.0
        EXPECT_EQ(*(float*) dataObjectData, numberOfElements - (i + 1));
    }

    EXPECT_EQ(listElementAtIndexPosition(list, numberOfElements), (DataObject *) NULL);
}

TEST_F(ListTest, listDeleteFromFrontOf)
{
    int inclusions = 11;
    int removals = 4;
    
    for(int i = 0; i < inclusions; ++i)
    {
        int status = listInsertToFrontOf(list, NULL);
        EXPECT_EQ(status, SUCCESS);
    }
    
    EXPECT_EQ(listGetLength(list), inclusions);
    
    for(int i = 0; i < removals; ++i)
    {
        listDeleteFromFrontOf(list);
    }

    EXPECT_EQ(listGetLength(list), inclusions - removals);

    for(int i = removals; i < inclusions; ++i)
    {
        listDeleteFromFrontOf(list);
    }

    EXPECT_EQ(listGetLength(list), 0);
}

TEST_F(ListTest, listPopFromFrontOf)
{
    int numberOfElements = 5;

    populateListWithFloats(list, numberOfElements, 0);

    for(int i = 0; i < numberOfElements; ++i)
    {
        DataObject * dataObject = listPopFromFrontOf(list);

        EXPECT_EQ(listGetLength(list), numberOfElements-(i+1));

        float * retrievedPointerValue;
        size_t retrievedValueSize;

        dataObjectGetWrappedData(dataObject, (void**) &retrievedPointerValue, &retrievedValueSize);

        float retrievedValue = *retrievedPointerValue;
        
        // Verifies if List == {4.0, 3.0, 2.0, 1.0, 0.0}
        EXPECT_EQ(retrievedValue, (numberOfElements-i)-1);

        dataObjectDestroy(dataObject);
    }
}

TEST_F(ListTest, listGetLength)
{
    EXPECT_EQ(listGetLength(list), 0);
    listInsertToFrontOf(list, NULL);
    EXPECT_EQ(listGetLength(list), 1);
    listInsertToFrontOf(list, NULL);
    EXPECT_EQ(listGetLength(list), 2);
    listPopFromFrontOf(list);
    EXPECT_EQ(listGetLength(list), 1);
    listPopFromFrontOf(list);
    EXPECT_EQ(listGetLength(list), 0);
}

TEST_F(ListTest, listSort)
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

    listSort(&list, compareFloats, 1);
    isSorted = listVerifyIfIsSorted(list, compareFloats, 1);
    EXPECT_EQ(isSorted, 1);

    listSort(&list, compareFloats, 0);
    isSorted = listVerifyIfIsSorted(list, compareFloats, 0);
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
    int status = populateListWithFloats(list, numberOfListElementsDuringStressTest, 1);
    int isSorted;

    if(status != SUCCESS)
    {
        EXPECT_EQ(status, SUCCESS);
        std::cout << "populateListWithFloatsDecreasing failed \n" << std::endl;
        return;
    }


    #if defined(__linux__)
        clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &start);
    #else
        ftime(&start);
    #endif
    
    listSort(&list, compareFloats, 1);
    
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

    size_t listSizeInBytes = listGetSizeInBytes(list);
    isSorted = listVerifyIfIsSorted(list, compareFloats, 1);
    EXPECT_EQ(isSorted, 1);
}

TEST_F(ListTest, listSplitInHalves)
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

    listSplitInHalves(&list, &firstHalf, &secondHalf);

    EXPECT_EQ(listGetLength(firstHalf), 3);
    EXPECT_EQ(listGetLength(firstHalf), listGetLengthByCounting(firstHalf));
    EXPECT_EQ(listGetLength(secondHalf), 2);
    EXPECT_EQ(listGetLength(secondHalf), listGetLengthByCounting(secondHalf));

    listDestroy(firstHalf);
    listDestroy(secondHalf);
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


    #if defined(__linux__)
        clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &start);
    #else
        ftime(&start);
    #endif
    
    listSort(&list, compareFloats, 0);
    
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

    size_t listSizeInBytes = listGetSizeInBytes(list);
    isSorted = listVerifyIfIsSorted(list, compareFloats, 0);
    EXPECT_EQ(isSorted, 1);
}