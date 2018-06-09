#include <gtest/gtest.h>
#include <memory>
#include <bitset>
#include <ostream>

using namespace std;

class GTest : public ::testing::Test {

protected:
	virtual void SetUp() {
	}

	virtual void TearDown() {
	}
};


TEST_F(GTest, concrete_class_gtest){
}


int main(int argc, char *argv[]) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
