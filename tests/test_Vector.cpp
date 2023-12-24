#include <gtest/gtest.h>
#include <stdlib.h>
#include <stdio.h>

#include "Vector.h"
#include "DataObject.h"

#include "test_General_Helpers.h"
#include "test_Vector_Helpers.h"

class VectorTest : public testing::Test
{
protected:
    void SetUp() override
    {
        vector = vectorCreate();
        
    }

    void TearDown() override
    {
        vectorDestroy(vector);
    }
    
    Vector * vector;

};

TEST_F(VectorTest, vectorCreate)
{
    EXPECT_EQ(vectorGetLength(vector), 0);
    EXPECT_EQ(vectorGetMaxCapacity(vector), 0);
    DataObject ** dataObject = vectorGetObjectArrayPointer(vector);
    EXPECT_EQ(dataObject, nullptr);
}

TEST_F(VectorTest, vectorInitialize)
{
    int vectorMaxCapacity = 4;
    vectorInitialize(vector, vectorMaxCapacity);
    EXPECT_EQ(vectorGetLength(vector), 0);
    EXPECT_EQ(vectorGetMaxCapacity(vector), vectorMaxCapacity);
    DataObject ** dataObject = vectorGetObjectArrayPointer(vector);
    EXPECT_NE(dataObject, nullptr);
}

TEST_F(VectorTest, vectorPushBack)
{
    int vectorMaxCapacity = 10;
    int numberOfInsertions = 4;
    vectorInitialize(vector, vectorMaxCapacity);
    populateVectorWithFloats(vector, numberOfInsertions, 0);
    EXPECT_EQ(vectorGetLength(vector), numberOfInsertions);
    EXPECT_EQ(vectorGetMaxCapacity(vector), vectorMaxCapacity);
}

TEST_F(VectorTest, vectorPopBack)
{
    int vectorMaxCapacity = 10;
    int numberOfInsertions = 4;
    vectorInitialize(vector, vectorMaxCapacity);
    populateVectorWithFloats(vector, numberOfInsertions, 0);
    EXPECT_EQ(vectorGetLength(vector), numberOfInsertions);
    DataObject * dataObject = vectorPopBack(vector);
    EXPECT_NE(dataObject, nullptr);
    EXPECT_EQ(vectorGetLength(vector), numberOfInsertions - 1);
}

TEST_F(VectorTest, vectorPeekElementAtPositionIndex)
{
    int vectorMaxCapacity = 10;
    int numberOfInsertions = 1;
    vectorInitialize(vector, vectorMaxCapacity);
    populateVectorWithFloats(vector, numberOfInsertions, 0);
    DataObject * dataObject = vectorPeekElementAtPositionIndex(vector, 0);
    EXPECT_NE(dataObject, nullptr);

    float * zeroPointer;
    size_t zeroPointerSize;

    dataObjectGetWrappedData(dataObject, (void**) &zeroPointer, &zeroPointerSize);
    EXPECT_EQ(*zeroPointer, 0);
}

TEST_F(VectorTest, vectorSwapElementsAtPositionIndexes)
{
    int vectorMaxCapacity = 10;
    int numberOfInsertions = 2;
    vectorInitialize(vector, vectorMaxCapacity);
    populateVectorWithFloats(vector, numberOfInsertions, 0);
    DataObject * dataObject1 = vectorPeekElementAtPositionIndex(vector, 0);
    DataObject * dataObject2 = vectorPeekElementAtPositionIndex(vector, 1);

    float * zeroPointer;
    size_t zeroPointerSize;

    float * onePointer;
    size_t onePointerSize;

    dataObjectGetWrappedData(dataObject1, (void**) &zeroPointer, &zeroPointerSize);
    dataObjectGetWrappedData(dataObject2, (void**) &onePointer, &onePointerSize);

    EXPECT_EQ(*zeroPointer, 0);
    EXPECT_EQ(*onePointer, 1);

    vectorSwapElementsAtPositionIndexes(vector, 0, 1);

    dataObject1 = vectorPeekElementAtPositionIndex(vector, 0);
    dataObject2 = vectorPeekElementAtPositionIndex(vector, 1);

    dataObjectGetWrappedData(dataObject1, (void**) &zeroPointer, &zeroPointerSize);
    dataObjectGetWrappedData(dataObject2, (void**) &onePointer, &onePointerSize);

    EXPECT_EQ(*zeroPointer, 1);
    EXPECT_EQ(*onePointer, 0);
}

TEST_F(VectorTest, vectorDestroy)
{
    vectorDestroy(vector);
    vector = NULL;
}