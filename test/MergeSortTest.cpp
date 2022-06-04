#include "gtest/gtest.h"

#include "algorithms/MergeSort.h"
#include "algorithms/LinkedList.h"

TEST(HeapTest, shouldSortList) {
    LinkedList<int> list;

    list.pushBack(3);
    list.pushBack(7);
    list.pushBack(10);
    list.pushBack(1);
    list.pushBack(4);

    mergeSort(&list);
    Node<int>* node;

    node = list.getHeadNode();

    ASSERT_EQ(1, node->data);
    node = node->next;

    ASSERT_EQ(3, node->data);
    node = node->next;

    ASSERT_EQ(4, node->data);
    node = node->next;

    ASSERT_EQ(7, node->data);
    node = node->next;

    ASSERT_EQ(10, node->data);
    node = node->next;

    ASSERT_EQ(nullptr, node);
}

TEST(HeapTest, shouldHandleListWithSizeTwo) {
    LinkedList<int> list;

    list.pushBack(10);
    list.pushBack(7);


    mergeSort(&list);

    Node<int>* node = list.getHeadNode();

    ASSERT_EQ(7, node->data);
    node = node->next;

    ASSERT_EQ(10, node->data);
}

TEST(HeapTest, shouldHandleEmptyList) {
    LinkedList<int> list;


    mergeSort(&list);

    ASSERT_EQ(0, list.size());
    ASSERT_EQ(nullptr, list.getHeadNode());
}