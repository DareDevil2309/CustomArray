#include "pch.h"
#include "Array.h"
#include <string>

namespace ArrayTest {
    TEST(DefaultConstructorTest, CorrectCapacity) {
        Array<std::string> arr;
        EXPECT_EQ(arr.capacity(), 8);
    }

    TEST(DefaultConstructorTest, CorrectSize) {
        Array<std::string> arr;
        EXPECT_EQ(arr.size(), 0);
    }

    TEST(CapacityConstructorTest, CorrectCapacity) {
        int capacity = 10;
        Array<std::string> arr(capacity);
        EXPECT_EQ(arr.capacity(), capacity);
    }

    TEST(CapacityConstructorTest, CorrectSize) {
        Array<std::string> arr(10);
        EXPECT_EQ(arr.size(), 0);
    }

    TEST(TakeElementTest, InvalidIndexThrowsException) {
        Array<std::string> arr(1);
        std::string s = "Hello world";
        arr.insert(s);
        EXPECT_ANY_THROW(arr[1]);
    }

    TEST(InsertReferenceTest, ArrayHasCorrectValue) {
        Array<std::string> arr;
        std::string s = "Hello world";
        arr.insert(s);
        EXPECT_EQ(arr[0], s);
    }

    TEST(InsertReferenceTest, MultipleInsertHasCorrectValues) {
        Array<std::string> arr;
        std::string s1 = "Hello ";
        std::string s2 = "world";
        arr.insert(s1);
        arr.insert(s2);
        EXPECT_EQ(arr[0], s1);
        EXPECT_EQ(arr[1], s2);
    }

    TEST(InsertReferenceIndexTest, ArrayHasCorrectValue) {
        Array<std::string> arr(10);
        std::string s = "Hello world";
        arr.insert(0, s);
        arr.insert(1, s);
        arr.insert(2, s);
        arr.insert(1, "Test");
        EXPECT_EQ(arr[1], "Test");
    }

    TEST(InsertValueTest, ArrayHasCorrectValue) {
        Array<std::string> arr;
        arr.insert("Test");
        EXPECT_EQ(arr[0], "Test");
    }

    TEST(InsertReferenceTest, InvalidIndexThrowsOutOfRangeException) {
        Array<std::string> arr;
        std::string s = "Hello world";
        EXPECT_ANY_THROW(arr.insert(8, s));
    }

    TEST(RemoveTest, InvalidIndexThrowsException) {
        Array<std::string> arr;
        arr.insert("Test");
        EXPECT_ANY_THROW(arr.remove(2));
    }

    TEST(RemoveTest, RemoveCorrect) {
        Array <std::string> arr;
        arr.insert("Test");
        EXPECT_EQ(arr.size(), 1);
        arr.remove(0);
        EXPECT_EQ(arr.size(), 0);
        EXPECT_ANY_THROW(arr[0]);
    }
}