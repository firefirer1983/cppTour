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



int count_char_x(const char *str, char x) {
	int cnt = 0;
	while(str&&*str) {
		if(*str == x)
			++cnt;
		++str;
	}
	return cnt;
}

TEST_F(GTest, pointer_char_special_value_gtest){
	EXPECT_FALSE(static_cast<bool>(nullptr));
	EXPECT_FALSE(0);
	EXPECT_FALSE('\0');
	EXPECT_EQ(count_char_x("xxx  yy\r\n  yzzz",'x'), 3);
}
void wait_input(void) {
	string direction;
	while(1) {
		cout << "input direction" <<endl;
		cin >> direction;
		printf("direction:%s, size:%lu \n",direction.c_str(), direction.size());
		switch(direction[0]) {
			case 'p':
				printf("UP\n");
				break;
			case 'n':
				printf("DOWN\n");
				break;
			case 'f':
				printf("RIGHT\n");
				break;
			case 'b':
				printf("LEFT\n");
				break;
			case 'q':
				return ;
		}
	}
}
TEST_F(GTest, cin_input_value_gtest){
	string dir{"p"};
	EXPECT_EQ(dir.size(), 1);
	wait_input();
}

// 数组名绝对不是指针变量，而是代表数组这种数据结构，只是可以在参与运算时转化为指针常量
// 将数组名作为实参传给函数，在函数内部使用的时候，数组名就会自动退化为指向数组首个元素的指针。
// 为了避免这种情况发生，如果需要将数组名与其信息传入函数内部，可以传数组名的引用。
// T ary[N];
// sizeof(ary) ===> N*sizeof(T);
// size_t aryMemberSize(T ary[]){ return sizeof(*ary)}; ===> sizeof(T)
// template<typename T, int N>
// constexpr size_t arySize(T (&ary)[N]){ return reinterpret_cast<size_t>(&arr+1) - reinterpret_cast<size_t>(arr); } ===> N*sizeof(T)
template<int N>
int startWith(const string &str, const char (&prefix)[N]) {
	return str.size() >= N-1&&equal(prefix, prefix+N-1, str.begin());
}

template<typename T,int N>
void print_array(const T (&ary)[N]) {
	for(const auto &x:ary)
		cout << x << " ";
	printf("\n");
}

template<int N>
constexpr size_t array_size(int (&arr)[N]) {
	return static_cast<size_t>(reinterpret_cast<size_t>(&arr+1) - reinterpret_cast<size_t>(arr));
}

TEST_F(GTest, array_gtest) {
	char charArray[]{"hello world!"};
	int intArray[]{1,2,3,4,5};

	print_array(charArray);
	print_array(intArray);

	EXPECT_EQ(*charArray, charArray[0]);
	EXPECT_EQ(charArray, &charArray[0]);

	printf("%p\n", intArray);
	unsigned long int array_begin = reinterpret_cast<unsigned long int>(intArray);
	unsigned long int array_end = reinterpret_cast<unsigned long int>(&intArray+1);
	EXPECT_EQ((array_end-array_begin), sizeof(intArray));

	const int size = 3;

	int d2Array[size][size]{{1,2,3},{4,5,6},{7,8,9}};
//	int ddArray[][size]{1,2,3,4,5,6,7,8,9};
	EXPECT_EQ(sizeof(d2Array[0]), size*sizeof(d2Array[0][0]));


	unsigned long int array2d_begin = reinterpret_cast<unsigned long int>(d2Array[0]);
	unsigned long int array2d_end = reinterpret_cast<unsigned long int>(&d2Array[0]+1);
	EXPECT_EQ((array2d_end-array2d_begin), size*sizeof(d2Array[0][0]));

	const int memCnt = 10;
	int testAry[memCnt];
	EXPECT_EQ(array_size(testAry), 10*sizeof(testAry[0]));
	EXPECT_EQ(array_size(d2Array[0]), 3*sizeof(d2Array[0][0]));
	static_assert(array_size(testAry)==memCnt*sizeof(int), "array size incorrect!");

}

int main(int argc, char *argv[]) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
