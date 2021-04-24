// Uncomment the next line to use precompiled headers
#include "pch.h"
// uncomment the next line if you do not use precompiled headers
//#include "gtest/gtest.h"
//
// the global test environment setup and tear down
// you should not need to change anything here
class Environment : public ::testing::Environment
{
public:
	~Environment() override {}

	// Override this to define how to set up the environment.
	void SetUp() override
	{
		//  initialize random seed
		srand(time(nullptr));
	}

	// Override this to define how to tear down the environment.
	void TearDown() override {}
};

// create our test class to house shared data between tests
// you should not need to change anything here
class CollectionTest : public ::testing::Test
{
protected:
	// create a smart point to hold our collection
	std::unique_ptr<std::vector<int>> collection;

	void SetUp() override
	{ // create a new collection to be used in the test
		collection.reset(new std::vector<int>);
	}

	void TearDown() override
	{ //  erase all elements in the collection, if any remain
		collection->clear();
		// free the pointer
		collection.reset(nullptr);
	}

	// helper function to add random values from 0 to 99 count times to the collection
	void add_entries(int count)
	{
		assert(count > 0);
		for (auto i = 0; i < count; ++i)
			collection->push_back(rand() % 100);
	}
};

// When should you use the EXPECT_xxx or ASSERT_xxx macros?
// Use ASSERT when failure should terminate processing, such as the reason for the test case.
// Use EXPECT when failure should notify, but processing should continue

// Test that a collection is empty when created.
// Prior to calling this (and all other TEST_F defined methods),
//  CollectionTest::StartUp is called.
// Following this method (and all other TEST_F defined methods),
//  CollectionTest::TearDown is called
TEST_F(CollectionTest, CollectionSmartPointerIsNotNull)
{
	// is the collection created
	ASSERT_TRUE(collection);

	// if empty, the size must be 0
	ASSERT_NE(collection.get(), nullptr);
}

// Test that a collection is empty when created.
TEST_F(CollectionTest, IsEmptyOnCreate)
{
	// is the collection empty?
	ASSERT_TRUE(collection->empty());

	// if empty, the size must be 0
	ASSERT_EQ(collection->size(), 0);
}

/* Comment this test out to prevent the test from running
 * Uncomment this test to see a failure in the test explorer */
 //TEST_F(CollectionTest, AlwaysFail)
 //{
 //	FAIL();
 //}

 // DONE: Create a test to verify adding a single value to an empty collection
TEST_F(CollectionTest, CanAddToEmptyVector)
{
	// is the collection empty?
	ASSERT_TRUE(collection->empty());

	// if empty, the size must be 0
	ASSERT_EQ(collection->size(), 0);

	add_entries(1);

	// is the collection still empty?
	ASSERT_FALSE(collection->empty());

	// if not empty, what must the size be?
	ASSERT_EQ(collection->size(), 1);

}

// DONE: Create a test to verify adding five values to collection
TEST_F(CollectionTest, CanAddFiveValuesToVector)
{
	// is the collection empty?
	ASSERT_TRUE(collection->empty());

	// if empty, the size must be 0
	ASSERT_EQ(collection->size(), 0);

	add_entries(5);

	// is the collection still empty?
	ASSERT_FALSE(collection->empty());

	// if not empty, what must the size be?
	ASSERT_EQ(collection->size(), 5);
}

// DONE: Create a test to verify that max size is greater than or equal to size for 0, 1, 5, 10 entries
TEST_F(CollectionTest, MaxSizeGreaterThanSize)
{
	ASSERT_EQ(collection->size(), 0);
	ASSERT_GE(collection->max_size(), collection->size());

	add_entries(1);
	ASSERT_GE(collection->max_size(), collection->size());

	collection->clear();
	add_entries(5);
	ASSERT_GE(collection->max_size(), collection->size());

	collection->clear();
	add_entries(10);
	ASSERT_GE(collection->max_size(), collection->size());
}

// DONE: Create a test to verify that capacity is greater than or equal to size for 0, 1, 5, 10 entries
TEST_F(CollectionTest, CapacityGreaterThanSize)
{
	ASSERT_EQ(collection->size(), 0);
	ASSERT_GE(collection->capacity(), collection->size());

	add_entries(1);
	ASSERT_GE(collection->capacity(), collection->size());

	collection->clear();
	add_entries(5);
	ASSERT_GE(collection->capacity(), collection->size());

	collection->clear();
	add_entries(10);
	ASSERT_GE(collection->capacity(), collection->size());
}

// DONE: Create a test to verify resizing increases the collection
TEST_F(CollectionTest, ResizeIncreasesSize)
{
	ASSERT_EQ(collection->size(), 0);

	collection->resize(10);

	ASSERT_EQ(collection->size(), 10);
}

// DONE: Create a test to verify resizing decreases the collection
TEST_F(CollectionTest, ResizeDecreasesSize)
{
	ASSERT_EQ(collection->size(), 0);

	add_entries(10);

	ASSERT_EQ(collection->size(), 10);

	collection->resize(5);

	ASSERT_EQ(collection->size(), 5);
}

// DONE: Create a test to verify resizing decreases the collection to zero
TEST_F(CollectionTest, ResizeDecreasesToZero)
{
	ASSERT_EQ(collection->size(), 0);

	add_entries(10);

	ASSERT_EQ(collection->size(), 10);

	collection->resize(0);

	ASSERT_EQ(collection->size(), 0);
}

// DONE: Create a test to verify clear erases the collection
TEST_F(CollectionTest, ClearErasesCollection)
{
	ASSERT_EQ(collection->size(), 0);

	add_entries(10);

	ASSERT_EQ(collection->size(), 10);

	collection->clear();

	ASSERT_EQ(collection->size(), 0);
}

// DONE: Create a test to verify erase(begin,end) erases the collection
TEST_F(CollectionTest, EraseErasesCollection)
{
	EXPECT_EQ(collection->size(), 0);

	add_entries(10);

	ASSERT_EQ(collection->size(), 10);

	collection->erase(collection->begin(), collection->end());

	ASSERT_EQ(collection->size(), 0);
}

// DONE: Create a test to verify reserve increases the capacity but not the size of the collection
TEST_F(CollectionTest, ReserveIncreasesCapacityNotSize)
{
	ASSERT_EQ(collection->size(), 0);

	EXPECT_LT(collection->capacity(), 10);

	collection->reserve(10);

	ASSERT_EQ(collection->capacity(), 10);

	ASSERT_EQ(collection->size(), 0);
}

// DONE: Create a test to verify the std::out_of_range exception is thrown when calling at() with an index out of bounds
// NOTE: This is a negative test
TEST_F(CollectionTest, OutOfRangeExceptionThrown)
{
	ASSERT_EQ(collection->size(), 0);

	ASSERT_THROW(collection->at(1), std::out_of_range);
}

// DONE: Create 2 unit tests of your own to test something on the collection - do 1 positive & 1 negative
// JR: Verifies that shrink_to_fit reduces capacity() to match size()
TEST_F(CollectionTest, ShrinkFreesUnusedMemory)
{
	EXPECT_EQ(collection->size(), 0);

	add_entries(10);

	collection->erase(collection->end() - 5, collection->end());

	collection->shrink_to_fit();

	ASSERT_EQ(collection->size(), collection->capacity());
}

// JR: Verifies that std::length_error exception is thrown when exceeding max_size 
TEST_F(CollectionTest, LengthErrorExceptionThrown)
{
	EXPECT_EQ(collection->size(), 0);

	ASSERT_THROW(collection->resize(collection->max_size() + 1), std::length_error);
}