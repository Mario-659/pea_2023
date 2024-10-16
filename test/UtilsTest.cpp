#include "gtest/gtest.h"

#include "utils/Utils.h"

/* TODO test is not passing, probably should mock file reader as path of test file depends on execution path
TEST(fileReader, shouldReadFromFileInExpectedOrder) {
    std::vector<std::vector<int>> expected{
            std::vector<int>{ 10, 6, 0, 5 },
            std::vector<int>{ 0, 1, 16 },
            std::vector<int>{ 0, 2, 13 },
            std::vector<int>{ 1, 2, 10 },
            std::vector<int>{ 1, 3, 12 },
            std::vector<int>{ 2, 1, 4 },
            std::vector<int>{ 2, 4, 14 },
            std::vector<int>{ 3, 2, 9 },
            std::vector<int>{ 3, 5, 20 },
            std::vector<int>{ 4, 3, 7 },
            std::vector<int>{ 4, 5, 4 }
    };

    auto actual = utils::readFromFile("resources/testParams.txt");

    ASSERT_EQ(expected.size(), actual.size()) << "Sizes of arrays don't match. Expected: " << expected.size() << " , actual:" << actual.size();

    for(int i=0; i<expected.size(); i++) {
        auto params = expected[i];
        for(int j=0; j<params.size(); j++) {
            EXPECT_EQ(params[j], actual[i][j]) << "expected[" << i << "][" << j << "]=" << expected[i][j] << ", actual[" << i << "][" << j << "]=" << actual[i][j];
        }
    }
}
*/

TEST(randomVector, shouldReturnRandomVectorWithGivenSize) {
    int SIZE = 57;
    std::vector<int> actual = utils::getRandVect(SIZE, 0, 100);
    ASSERT_EQ(SIZE, actual.size());
}

TEST(randomVector, shouldReturnRandomVectorInGivenRange) {
    int MIN = -10;
    int MAX = 10;
    int SIZE = 100;
    std::vector<int> actual = utils::getRandVect(SIZE, MIN, MAX);

    for (int i=0; i<SIZE; i++) {
        ASSERT_TRUE(actual[i] >= MIN);
        ASSERT_TRUE(actual[i] <= MAX);
    }
}
