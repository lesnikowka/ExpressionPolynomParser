#include "gtest/gtest.h"


#include "hash-table(open-adressing).h"


class HT_fixture : public testing::Test {
protected:
	HashTableOpenAdressing<std::string, int> ht1;

	std::vector<std::pair<std::string, int>> v1 = { {"name1",1}, {"name2",2},{"123", 67}, {"1q2w3e", -100} };
};


TEST_F(HT_fixture, recomposing_will_happen_if_many_number_elements_is_added) {
	size_t cap = ht1.capacity();

	for (int i = 0; i <= cap * MAXIMUM_OCCUPANCY + 1; i++) {
		ht1.emplace(std::to_string(i), i);
	}

	EXPECT_GT(ht1.capacity(), cap);
}

TEST_F(HT_fixture, adding_many_elements) {
	for (int i = 0; i < 100000; i++) {
		ASSERT_NO_THROW(ht1.emplace(std::to_string(i), i));
	}
}

TEST_F(HT_fixture, iterators_are_working) {
	for (auto i : v1) {
		ht1.insert(i);
	}

	for (auto i : v1) {
		EXPECT_FALSE(ht1.find(i.first) == ht1.end());
	}

	for (auto i : ht1) {
		EXPECT_FALSE(std::find(v1.begin(), v1.end(), i) == v1.end());
	}
}