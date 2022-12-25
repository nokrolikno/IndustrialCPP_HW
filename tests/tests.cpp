#include <gtest/gtest.h>
#include <stdio.h>
#include <string>
#include <vector>

#include "../include/set.hpp"

TEST(addition, Basecase) {
  StringHasher h;
  Set<std::string, StringHasher> hash_set(8, h);
  EXPECT_TRUE(hash_set.add("a", "b"));
  EXPECT_TRUE(hash_set.add("c", "d"));
  EXPECT_FALSE(hash_set.add("a", "q"));
}

TEST(Get, Basecase) {
  StringHasher h;
  Set<std::string, StringHasher> hash_set(8, h);
  EXPECT_TRUE(hash_set.add("str1", "a"));
  EXPECT_EQ(hash_set.get("str1"), "a");
  EXPECT_EQ(hash_set.get("str2"), "");
}

TEST(Delete, Basecase) {
  StringHasher h;
  Set<std::string, StringHasher> hash_set(8, h);
  EXPECT_TRUE(hash_set.add("str1", "a"));
  EXPECT_TRUE(hash_set.remove("str1"));
  EXPECT_FALSE(hash_set.remove("str1"));
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
