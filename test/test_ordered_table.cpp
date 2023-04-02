#include "gtest/gtest.h"
#include "ordered-table.h"
#include <vector>

class OT_fixture : public ::testing::Test{
protected:
	OrderedTable<int, int> o;
	std::vector<int> v = { 4, 3, 10, 8, 12, 13, 1 };
};

TEST_F(OT_fixture, no_throw_if_insert_in_ordered_table) { 
	for (int i = 0; i < 10; i++) {
		ASSERT_NO_THROW(o.insert({ i, i }));
	}
}

TEST_F(OT_fixture, no_throw_if_emplace_in_ordered_table) {
	for (int i = 0; i < 10; i++) {
		ASSERT_NO_THROW(o.emplace( i, i ));
	}
}

TEST_F(OT_fixture, no_throw_if_find_in_ordered_table) {
	for (int i = 0; i < 10; i++) {
		o.emplace(i, i);
	}

	for (int i = 0; i < 10; i++) {
		ASSERT_NO_THROW(o.find(i));
	}
}

TEST_F(OT_fixture, no_throw_if_find_in_empty_ordered_table) {
	for (int i = 0; i < 10; i++) {
		ASSERT_NO_THROW(o.find(i));
	}
}

TEST_F(OT_fixture, end_if_element_not_found_in_ordered_table) {
	for (int i = 0; i < 10; i++) {
		o.emplace(i, i);
	}

	EXPECT_TRUE(o.find(10) == o.end());
}

TEST_F(OT_fixture, not_end_if_element_not_found_in_ordered_table) {
	for (int i = 0; i < 10; i++) {
		o.emplace(i, i);
	}

	EXPECT_FALSE(o.find(5) == o.end());
}

TEST_F(OT_fixture, can_insert_and_find_element_without_erase_in_ordered_table) {
	for (int i = 0; i < v.size(); i++) {
		o.emplace(v[i], v[i]);
	}

	for (int i = 0; i < v.size(); i++) {
		EXPECT_EQ((*(o.find(v[i]))), std::make_pair(v[i],v[i]));
	}
}

TEST_F(OT_fixture, can_insert_and_find_element_with_erase_in_ordered_table) {
	for (int i = 0; i < v.size(); i++) {
		o.emplace(v[i], v[i]);
	}

	o.erase(10);
	o.erase(3);

	v.erase(std::find(v.begin(), v.end(), 10));

	v.erase(std::find(v.begin(), v.end(), 3));


	for (int i = 0; i < v.size(); i++) {
		EXPECT_EQ((*(o.find(v[i]))), std::make_pair(v[i], v[i]));
	}
}

TEST_F(OT_fixture, throw_if_erase_not_existing_element_in_ordered_table) {
	for (int i = 0; i < v.size(); i++) {
		o.emplace(v[i], v[i]);
	}

	ASSERT_ANY_THROW(o.erase(-2));
}

TEST_F(OT_fixture, throw_if_erase_in_empty_ordered_table) {
	ASSERT_ANY_THROW(o.erase(-2));
}

TEST_F(OT_fixture, ordered_table_can_sort_elements) {
	for (int i = 0; i < v.size(); i++) {
		o.emplace(v[i], v[i]);
	}

	std::sort(v.begin(), v.end());

	auto i1 = o.begin();
	auto i2 = v.begin();

	while (i2 != v.end()) {
		EXPECT_EQ((*i1).first, *i2);
		++i1;
		++i2;
	}
}

TEST_F(OT_fixture, can_copy_ordered_table) {
	OrderedTable<int, int> o2 = o;

	EXPECT_EQ(o, o2);
}

TEST_F(OT_fixture, can_move_ordered_table_in_ctor) {
	OrderedTable<int, int> o2 = o;
	OrderedTable<int, int> o3 = std::move(o);

	EXPECT_EQ(o3, o2);
}

TEST_F(OT_fixture, can_assign_ordered_table) {
	OrderedTable<int, int> o2;

	o2 = o;

	EXPECT_EQ(o, o2);
}

TEST_F(OT_fixture, can_move_ordered_table_in_assign_operator) {
	OrderedTable<int, int> o2 = o;
	OrderedTable<int, int> o3;

	o3 = std::move(o);

	EXPECT_EQ(o3, o2);
}



TEST_F(OT_fixture, throw_if_deference_end_iterator) {
	ASSERT_ANY_THROW(*(o.end()));
}

TEST_F(OT_fixture, iterators_are_working) {
	for (auto i : v) {
		o.emplace(i,i);
	}

	for (auto i : v) {
		EXPECT_FALSE(o.find(i) == o.end());
	}

	for (auto i : o) {
		EXPECT_FALSE(std::find(v.begin(), v.end(), i.first) == v.end());
	}
}
