#include "gtest/gtest.h"
#include "test.h"

TEST(test, True)
{
	int a = 1;
	EXPECT_TRUE(test(a));
}

TEST(test, False)
{
	int a = -1;
	EXPECT_FALSE(test(a));
}
