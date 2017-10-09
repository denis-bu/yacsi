// TODO: implement UTs for kickoff here
//
//

#include "yacsi/kickoff.hpp"

#include <gtest/gtest.h>

TEST(kickoff_test_1, kickoff_test)
{
    EXPECT_EQ(42, yacsi::kickoff(21));
}

TEST(kickoff_test_mult, kickoff_test)
{
	EXPECT_EQ(34, yacsi::kickoff(17));
}

//int main() {
//	return 0;
//}
