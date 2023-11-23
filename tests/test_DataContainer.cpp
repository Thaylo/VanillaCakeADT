#include <gtest/gtest.h>
#include "../include/DataContainer/DataContainer.h"

class DataContainerTest : public testing::Test {
protected:
    void SetUp() override {
        // Initialization code that will be run before each test
        dataContainer = encapsulateDataOnDataContainer(nullptr, 0, nullptr, nullptr);
    }

    void TearDown() override {
        // Clean-up code that will be run after each test
        destroyDataContainer(&dataContainer);
    }

    // Member variables accessible in the tests
    DataContainer *dataContainer;
};

// Test case for encapsulateDataOnDataContainer
TEST_F(DataContainerTest, EncapsulateDataOnDataContainer) {
    void *testData = getDataPointerForTesting(dataContainer);
    EXPECT_EQ(testData, nullptr);
}