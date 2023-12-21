#include <gtest/gtest.h>
#include <stdlib.h>
#include <stdio.h>

#include "Stack.h"
#include "DataContainer.h"

class StackTest : public testing::Test
{
protected:
    void SetUp() override
    {
        stack = stackCreate();
        
    }

    void TearDown() override
    {
        destroyStack(stack);
    }
    
    Stack * stack;

};

TEST_F(StackTest, stackCreate)
{
    EXPECT_EQ(getStackLength(stack), 0);
}

TEST_F(StackTest, stackPush)
{
    DataContainer * d1 =
            encapsulateDataOnDataContainer(malloc(sizeof(int)), (size_t) 0, free, NULL);

    DataContainer * d2 =
            encapsulateDataOnDataContainer(malloc(sizeof(int)), (size_t) 0, free, NULL);

    stackPush(stack, d1);
    EXPECT_EQ(getStackLength(stack), 1);

    stackPush(stack, d2);
    EXPECT_EQ(getStackLength(stack), 2);
}

TEST_F(StackTest, stackPop)
{
    DataContainer * d1 =
            encapsulateDataOnDataContainer(malloc(sizeof(int)), (size_t) 0, free, NULL);

    DataContainer * d2 =
            encapsulateDataOnDataContainer(malloc(sizeof(int)), (size_t) 0, free, NULL);

    stackPush(stack, d1);
    stackPush(stack, d2);
    DataContainer * d2Recovered = stackPop(stack);
    EXPECT_NE(d2Recovered, nullptr);

    DataContainer * d1Recovered = stackPop(stack);
    EXPECT_NE(d1Recovered, nullptr);

    destroyDataContainer(d1);
    destroyDataContainer(d2);
}

TEST_F(StackTest, stackPeek)
{
    DataContainer * d1 =
            encapsulateDataOnDataContainer(malloc(sizeof(int)), (size_t) 0, free, NULL);

    DataContainer * d2 =
            encapsulateDataOnDataContainer(malloc(sizeof(int)), (size_t) 0, free, NULL);

    stackPush(stack, d1);
    stackPush(stack, d2);
    EXPECT_EQ(stackPeek(stack), d2);

    DataContainer * d2Recovered = stackPop(stack);

    EXPECT_EQ(stackPeek(stack), d1);

    destroyDataContainer(d2Recovered);
}

TEST_F(StackTest, getStackLength)
{
    DataContainer * d1 =
            encapsulateDataOnDataContainer(malloc(sizeof(int)), (size_t) 0, free, NULL);

    DataContainer * d2 =
            encapsulateDataOnDataContainer(malloc(sizeof(int)), (size_t) 0, free, NULL);

    stackPush(stack, d1);
    stackPush(stack, d2);
    EXPECT_EQ(getStackLength(stack), 2);

    stackPop(stack);
    EXPECT_EQ(getStackLength(stack), 1);

    stackPop(stack);
    EXPECT_EQ(getStackLength(stack), 0);

    destroyDataContainer(d1);
    destroyDataContainer(d2);
}


// This test actualy does not test if destroyStack makes the intended changes but highlights a caveat
// See  the comments below.
// TODO: for memory safety, consider implementing "destroyAndSetToNull" functions
TEST_F(StackTest, destroyStack)
{
    DataContainer * d1 =
            encapsulateDataOnDataContainer(malloc(sizeof(int)), (size_t) 0, free, NULL);

    DataContainer * d2 =
            encapsulateDataOnDataContainer(malloc(sizeof(int)), (size_t) 0, free, NULL);

    stackPush(stack, d1);
    stackPush(stack, d2);
    EXPECT_EQ(getStackLength(stack), 2);

    destroyStack(stack); // does not destroy the address stored in stack
    stack = nullptr; // without this line the next line would segfault

    EXPECT_EQ(getStackLength(stack), 0); // stack is now a nullptr so it is expected to h
}