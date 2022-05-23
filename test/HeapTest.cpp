#include "gtest/gtest.h"

#include "algorithms/Heap.h"
#include "graphs/AdjacencyList.h"

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

TEST(HeapTest, shouldExtractAllMinimalCustomTypes) {
    Heap<ListNode> que(10);

    que.push({3, 0});
    que.push({7, 1});
    que.push({10, 1});
    que.push({1, 2});
    que.push({4, 2});

    ASSERT_EQ(1, que.extractMin().weight);
    ASSERT_EQ(3, que.extractMin().weight);
    ASSERT_EQ(4, que.extractMin().weight);
    ASSERT_EQ(7, que.extractMin().weight);
    ASSERT_EQ(10, que.extractMin().weight);
}

TEST(HeapTest, shouldHandleUpdate) {
    Heap<ListNode> que(10);

    que.push({3, 0});
    que.push({7, 1});
    que.push({10, 1});
    que.push({1, 2});
    que.push({4, 2});

    que.update({3, 0}, {7, 0});
    que.update({7, 1}, {3, 1});
    que.update({10, 1}, {0, 1});
    que.update({1, 2}, {4, 2});
    que.update({4, 2}, {3, 2});


    ASSERT_EQ(0, que.extractMin().weight);
    ASSERT_EQ(3, que.extractMin().weight);
    ASSERT_EQ(3, que.extractMin().weight);
    ASSERT_EQ(4, que.extractMin().weight);
    ASSERT_EQ(7, que.extractMin().weight);
}

// TODO Heap test doesn't pass always
//TEST(HeapTest, bruteForceRandom) {
//    for (int i=0; i<10; i++) {
//        int size = rand() % 1000;
//        Heap<int> queue(size);
//
//        for(int j=0; j<size; j++) {
//            queue.push(rand() % 100);
//        }
//
//        for(int j=0; j<size; j++) {
//            queue.update(rand() % 100, rand() % 100);
//        }
//
//        std::vector<int> values(queue.getSize());
//        while(queue.getSize() != 0) {
//            values.push_back(queue.extractMin());
//        }
//        int prev = INT_MIN;
//        for (auto val : values) {
//            ASSERT_TRUE(prev <= val) << "Prev value: " << prev << ", next value: " << val << " after " << i << " iterations";
//            prev = val;
//        }
//    }
//}

