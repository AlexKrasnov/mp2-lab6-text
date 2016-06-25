#include "gtest.h"
#include "TStack.h"

TEST(Stack, can_create_stack)
{
	ASSERT_NO_THROW (TStack<int> St);
}

TEST(Stack, can_create_stack_with_positive_length)
{
	ASSERT_NO_THROW (TStack<int> A(5));
}

TEST(Stack, throws_when_create_Stack_with_negative_length)
{
	ASSERT_ANY_THROW(TStack<int> A(-2));
}

TEST(Stack, throws_when_create_Stack_with_very_big_length)
{
	ASSERT_ANY_THROW(TStack<int> A(301));
}

TEST(Stack, can_get_length)
{
	TStack<int> A(3);
	EXPECT_EQ(3, A.GetSize());
}

TEST(Stack, can_get_top)
{
	TStack<int> A(2);
	EXPECT_EQ(-1, A.GetTop());
}

TEST(Stack, can_get_top_2)
{
	TStack<double> A(2);
	A.push(1.5);
	A.pop();
	EXPECT_EQ(-1, A.GetTop());
}

TEST(Stack,can_push)
{
	TStack<int> A(5);
	ASSERT_NO_THROW(A.push(1));
}

TEST(Stack,can_pop)
{
	TStack<char> A(5);
	A.push('a');
	ASSERT_NO_THROW(A.pop());
}

TEST(Stack,can_push_and_pop_right)
{
	TStack<int> A(5);
	A.push(5);
	EXPECT_EQ(5, A.pop());
}

TEST(Stack,can_look_right)
{
	TStack<char> A(5);
	A.push('s');
	EXPECT_EQ('s', A.Top());
}

TEST(Stack, throws_when_full)
{
	TStack<bool> A(2);
	A.push(true);
	A.push(false);
	ASSERT_ANY_THROW(A.push(true));
}
TEST(Stack, throws_when_empty)
{
	TStack<int> A(2);
	ASSERT_ANY_THROW(A.pop());
}

TEST(Stack, compare_stack_full_return_true)
{
	TStack<float> S(2);
	S.push(1.5);
	S.push(0.5);
	EXPECT_EQ(true,S.GetTop()>=S.GetTop());
}

TEST(Stack, compare_stack_empty_return_true)
{
	TStack<int> S(2);
	EXPECT_EQ(true,S.GetTop()<0);
}