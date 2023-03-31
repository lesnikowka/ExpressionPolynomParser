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

TEST_F(HT_fixture, recomposing_dont_lose_elements) {
	std::vector<std::pair<std::string, int>> v2;
	for (int i = 0; i < 200; i++) {
		ht1.emplace(std::to_string(i), i);
		v2.push_back(std::pair<std::string, int> (std::to_string(i), i));
	}

	for (auto i : v2) {
		EXPECT_FALSE(ht1.find(i.first) == ht1.end());
	}
	for (auto i : ht1) {
		EXPECT_FALSE(std::find(v2.begin(), v2.end(), i) == v2.end());
	}
}

TEST_F(HT_fixture, size_is_correct) {
	for (int i = 0; i < 100; i++) {
		ASSERT_NO_THROW(ht1.emplace(std::to_string(i), i));
	}
	EXPECT_EQ(100, ht1.size());
}

TEST_F(HT_fixture, throw_if_deference_end_iterator) {
	ASSERT_ANY_THROW(*(ht1.end()));
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


TEST_F(HT_fixture, throw_if_erase_element_that_was_not_emplaced) {
	for (auto i : v1) {
		ht1.insert(i);
	}

	ASSERT_ANY_THROW(ht1.erase("name4"));
}


TEST_F(HT_fixture, can_erase_element) {
	for (auto i : v1) {
		ht1.insert(i);
	}

	ht1.erase("name2");
	v1.erase(std::find(v1.begin(), v1.end(), std::pair<std::string, int>("name2", 2)));

	for (auto i : v1) {
		EXPECT_FALSE(ht1.find(i.first) == ht1.end());
	}
	for (auto i : ht1) {
		EXPECT_FALSE(std::find(v1.begin(), v1.end(), i) == v1.end());
	}
}

TEST_F(HT_fixture, operator_square_brackets_can_return_element_reference) {
	for (auto i : v1) {
		ht1.insert(i);
	}

	ht1["name2"] = 999;
	v1[1].second = 999;

	for (auto i : v1) {
		EXPECT_FALSE(ht1.find(i.first) == ht1.end());
	}
	for (auto i : ht1) {
		EXPECT_FALSE(std::find(v1.begin(), v1.end(), i) == v1.end());
	}
}

TEST_F(HT_fixture, operator_square_brackets_can_add_element) {
	for (auto i : v1) {
		ht1.insert(i);
	}

	ht1["name5"] = 999;
	v1.push_back(std::pair<std::string, int>("name5", 999));

	for (auto i : v1) {
		EXPECT_FALSE(ht1.find(i.first) == ht1.end());
	}
	for (auto i : ht1) {
		EXPECT_FALSE(std::find(v1.begin(), v1.end(), i) == v1.end());
	}
}
