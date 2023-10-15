#include "gtest/gtest.h"

#include "algorithms/Heap.h"

TEST(HeapTest, shouldAddValues) {
    Heap<int> que(10);

    que.push(3);
    que.push(7);
    que.push(10);
    que.push(1);
    que.push(4);

    ASSERT_EQ(5, que.getSize());
}

TEST(HeapTest, shouldExtractTheSmallest) {
    Heap<int> que(10);

    que.push(3);
    que.push(7);
    que.push(10);
    que.push(1);
    que.push(4);

    ASSERT_EQ(1, que.extractMin());
}

TEST(HeapTest, sizeShouldChangeAfterExtract) {
    Heap<int> que(10);

    que.push(3);
    que.push(7);
    que.push(10);
    que.push(1);
    que.push(4);

    que.extractMin();
    ASSERT_EQ(4, que.getSize());
}

TEST(HeapTest, valueShouldNotBeInHeapAfterExtract) {
    Heap<int> que(10);

    que.push(3);
    que.push(7);
    que.push(10);
    que.push(1);
    que.push(4);

    que.extractMin();
    ASSERT_TRUE(1 != que.extractMin());
}

TEST(HeapTest, shouldExtractAllValues) {
    Heap<int> que(10);

    que.push(3);
    que.push(7);
    que.push(10);
    que.push(1);
    que.push(4);

    ASSERT_EQ(1, que.extractMin());
    ASSERT_EQ(3, que.extractMin());
    ASSERT_EQ(4, que.extractMin());
    ASSERT_EQ(7, que.extractMin());
    ASSERT_EQ(10, que.extractMin());
}
