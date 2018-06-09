#include <gtest/gtest.h>
#include <memory>
#include <bitset>

using namespace std;

class GTest : public ::testing::Test {

protected:
	virtual void SetUp() {
	}

	virtual void TearDown() {
	}
};

enum class EnumTypeLength { kLengthTest };
EnumTypeLength lenthTest = EnumTypeLength::kLengthTest;
TEST_F(GTest, basic_type_length_gtest){
	EXPECT_EQ(sizeof(bool), 1);
	EXPECT_EQ(sizeof(char), 1);
	EXPECT_EQ(sizeof(unsigned char), 1);
	EXPECT_EQ(sizeof(int), 4);
	EXPECT_EQ(sizeof(unsigned), 4);
	EXPECT_EQ(sizeof(float), 4);
	EXPECT_EQ(sizeof(double), 8);
	EXPECT_EQ(sizeof(long), 8);
	EXPECT_EQ(sizeof(unsigned long), 8);
	EXPECT_EQ(sizeof(unsigned long long), 8);
	EXPECT_EQ(sizeof(EnumTypeLength::kLengthTest), 4);
	EXPECT_EQ(sizeof(lenthTest), 4);
	EXPECT_EQ(sizeof(int*), 8);
	EXPECT_EQ(sizeof(void*), 8);
}


TEST_F(GTest, basic_type_operation_gtest){
	EXPECT_EQ(7%2, 1); // 7 - 2*(int)(7/2） = 7 - 2*(3) = 7 - 2*3 = 1;
	EXPECT_EQ((-7)%2, -1);// -7 - 2*(int)(-7/2) => -7 - 2 * int(-3) => -7 + 6 = -1;
	EXPECT_EQ(7%(-2), 1);//7 - (-2)*(int)(7/-2) = 7 - (-2)*(-3) = 7-8 = 1

	bitset<8> test_byte("01010111"); // 0x57
	EXPECT_EQ(static_cast<int>(test_byte.to_ulong()), 0x57);

	bitset<8>   fullone("11111111");
	EXPECT_EQ(static_cast<int>(fullone.to_ulong()), 0xFF);
	bitset<8> fullzero("00000000");
	EXPECT_EQ(static_cast<int>(fullzero.to_ulong()), 0x00);

	// xor
	bitset<8> result;
	result = fullone^fullzero;
	EXPECT_EQ(result.to_ulong(), 0xFF);
	EXPECT_STREQ(result.to_string().c_str(), "11111111");

	bitset<8> result1 = test_byte^fullone;
	EXPECT_STREQ(result1.to_string().c_str(), "10101000");

	bitset<8>result2 = test_byte^fullzero;
	EXPECT_STREQ(result2.to_string().c_str(), "01010111");

	bitset<8>result3 = result1^result2;
	EXPECT_STREQ(result3.to_string().c_str(), "11111111");

	// bit complement
	EXPECT_STREQ((~test_byte).to_string().c_str(), "10101000");

	EXPECT_EQ((bitset<8>(5)).to_string(), "00000101");
	EXPECT_EQ((~bitset<8>(5)).to_string(), "11111010");
	EXPECT_EQ((~bitset<8>(5)).to_ulong(), 0xFA);
}

TEST_F(GTest, basic_type_init_gtest){
	/* no warning at all */
	int i = 7.2;

	/* 为了兼容 c ，= 赋值操作不会产生 narrowing conversion 的warning，而是做了隐式的转换 */
	/* warning: narrowing conversion of ‘7.2000000000000002e+0’ from ‘double’ to ‘int’ inside { } [-Wnarrowing] */
//	int i2 = {7.2}; // this will get compile warning for information missing when instantiate
	int i2 = 7.2;
	EXPECT_EQ(i, 7);
	EXPECT_EQ(i2, 7);

	auto f = 7.2;
	EXPECT_NE(f, 7);
	i = f;
	EXPECT_EQ(i, 7);

}

namespace std {
	template <typename T, typename... Args>
	unique_ptr<T> make_unique(Args&&... args){
		return unique_ptr<T>{new T{forward<Args>(args)...}};
	};
}


class Parasite {
public:
	Parasite(const string &name, const string &parasitism=""):
			parasitism_(parasitism),
			name_(name)
	{
		if(parasitism_.empty())
			printf("%s Parasite hi!\n", name_.c_str());
		else
			printf("%s:%s Parasite hi!\n",parasitism_.c_str(), name_.c_str());
	}
	~Parasite() {
		if(parasitism_.empty())
			printf("%s Parasite die~\n", name_.c_str());
		else
			printf("%s:%s Parasite die~\n",parasitism_.c_str(), name_.c_str());
	}

private:
	string parasitism_;
	string name_;
};

class Parasitism {
public:
	Parasitism(const string &name):
			name_(name),
			parasite_("[Class]", name)
	{
		printf("%s Parasitism hello!\n", name_.c_str());
	}
	~Parasitism() {
		printf("%s Parasitism die~\n", name_.c_str());
	}


private:
	string name_;
	Parasite parasite_;
};

namespace Insect {
	Parasitism namespace_parasitism{"[NameSpace]"};
}

Parasite global_parasite{"[Global]"};

Parasitism global_parasitism{"[Global]"};

TEST_F(GTest, block_scope_and_life_gtest) {
	{
		Parasite block_parasite("[Block]");
	}
}

TEST_F(GTest, class_scope_and_life_gtest) {
	Parasitism *parasitism = new Parasitism("[Heap]");
	delete parasitism;
}


constexpr double power(double x) { return x*x; }

TEST_F(GTest, const_constexpr_gtest) {
	const int constant = 5;
	constexpr int constant_expr = power(constant);

	EXPECT_EQ(constant, 5);
	EXPECT_EQ(constant_expr, 25);
}

int main(int argc, char *argv[]) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
