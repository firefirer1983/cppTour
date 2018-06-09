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


enum class Color : unsigned char { kRed, kGreen, kBlue };
ostream &operator<<(ostream &out, Color color) {
	switch (color) {
		case Color::kRed:
			cout << "RED";
			break;
		case Color::kGreen:
			cout << "GREEN";
			break;
		case Color::kBlue:
			cout << "BLUE";
			break;
		default:
			cout << "Unknow Color";
			break;
	}
	return cout;
}

TEST_F(GTest, cout_enmu_gtest){
	Color c = Color ::kRed;
	cout << c << endl;
}

template <typename T>
class Vector {
public:
	Vector(size_t num):
			sz_(num),
			array_(new T[num])
	{

	}

	~Vector(){
		delete [] array_;
	}

	size_t size() {
		return sz_;
	}

	T &operator[](unsigned idx) {
		if(idx < sz_)
			return array_[idx];
		else
			return array_[sz_-1];
	}
private:
	size_t sz_;
	T *array_;
};

TEST_F(GTest, class_raii_gtest){
	const int vsize = 20;
	Vector<int> vInt(vsize);
	EXPECT_EQ(vInt.size(), vsize);
	vInt[0] = 10;
	vInt[19] = 19;
	EXPECT_EQ(vInt[19], 19);
	vInt[20] = 20;
	EXPECT_EQ(vInt[20], 20);
	EXPECT_EQ(vInt[19], 20);
}

union Value {
	char *name;
	unsigned idx;
};

TEST_F(GTest, union_gtest){
	Value v1;
	EXPECT_EQ(sizeof(v1), sizeof(char *));
	EXPECT_NE(sizeof(v1), sizeof(unsigned));
}

int main(int argc, char *argv[]) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
