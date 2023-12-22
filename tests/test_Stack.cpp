#include <gtest/gtest.h>
#include <stdlib.h>
#include <stdio.h>

#include "Stack.h"
#include "DataObject.h"

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
    DataObject * d1 =
            encapsulateDataOnDataObject(malloc(sizeof(int)), (size_t) 0, free, NULL);

    DataObject * d2 =
            encapsulateDataOnDataObject(malloc(sizeof(int)), (size_t) 0, free, NULL);

    stackPush(stack, d1);
    EXPECT_EQ(getStackLength(stack), 1);

    stackPush(stack, d2);
    EXPECT_EQ(getStackLength(stack), 2);
}

TEST_F(StackTest, stackPop)
{
    DataObject * d1 =
            encapsulateDataOnDataObject(malloc(sizeof(int)), (size_t) 0, free, NULL);

    DataObject * d2 =
            encapsulateDataOnDataObject(malloc(sizeof(int)), (size_t) 0, free, NULL);

    stackPush(stack, d1);
    stackPush(stack, d2);
    DataObject * d2Recovered = stackPop(stack);
    EXPECT_NE(d2Recovered, nullptr);

    DataObject * d1Recovered = stackPop(stack);
    EXPECT_NE(d1Recovered, nullptr);

    destroyDataObject(d1);
    destroyDataObject(d2);
}

TEST_F(StackTest, stackPeek)
{
    DataObject * d1 =
            encapsulateDataOnDataObject(malloc(sizeof(int)), (size_t) 0, free, NULL);

    DataObject * d2 =
            encapsulateDataOnDataObject(malloc(sizeof(int)), (size_t) 0, free, NULL);

    stackPush(stack, d1);
    stackPush(stack, d2);
    EXPECT_EQ(stackPeek(stack), d2);

    DataObject * d2Recovered = stackPop(stack);

    EXPECT_EQ(stackPeek(stack), d1);

    destroyDataObject(d2Recovered);
}

TEST_F(StackTest, getStackLength)
{
    DataObject * d1 =
            encapsulateDataOnDataObject(malloc(sizeof(int)), (size_t) 0, free, NULL);

    DataObject * d2 =
            encapsulateDataOnDataObject(malloc(sizeof(int)), (size_t) 0, free, NULL);

    stackPush(stack, d1);
    stackPush(stack, d2);
    EXPECT_EQ(getStackLength(stack), 2);

    stackPop(stack);
    EXPECT_EQ(getStackLength(stack), 1);

    stackPop(stack);
    EXPECT_EQ(getStackLength(stack), 0);

    destroyDataObject(d1);
    destroyDataObject(d2);
}


// This test actualy does not test if destroyStack makes the intended changes but highlights a caveat
// See  the comments below.
// TODO: for memory safety, consider implementing "destroyAndSetToNull" functions
TEST_F(StackTest, destroyStack)
{
    DataObject * d1 =
            encapsulateDataOnDataObject(malloc(sizeof(int)), (size_t) 0, free, NULL);

    DataObject * d2 =
            encapsulateDataOnDataObject(malloc(sizeof(int)), (size_t) 0, free, NULL);

    stackPush(stack, d1);
    stackPush(stack, d2);
    EXPECT_EQ(getStackLength(stack), 2);

    destroyStack(stack); // does not destroy the address stored in stack
    stack = nullptr; // without this line the next line would segfault

    EXPECT_EQ(getStackLength(stack), 0); // stack is now a nullptr so it is expected to h
}