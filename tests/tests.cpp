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

TEST(addition, ExpandRealloc) {
  StringHasher h;
  Set<std::string, StringHasher> hash_set(8, h);
  EXPECT_TRUE(hash_set.add("a", "a"));
  EXPECT_TRUE(hash_set.add("b", "b"));
  EXPECT_TRUE(hash_set.add("c", "c"));
  EXPECT_TRUE(hash_set.add("d", "d"));
  EXPECT_TRUE(hash_set.add("e", "e"));
  EXPECT_TRUE(hash_set.add("f", "f"));
  EXPECT_TRUE(hash_set.add("g", "g"));
  EXPECT_TRUE(hash_set.add("h", "h"));
  EXPECT_TRUE(hash_set.add("i", "i"));
  EXPECT_TRUE(hash_set.add("j", "j"));
  EXPECT_TRUE(hash_set.add("k", "k"));
  EXPECT_TRUE(hash_set.add("l", "l"));
  EXPECT_TRUE(hash_set.add("m", "m"));
  EXPECT_TRUE(hash_set.add("n", "n"));
  EXPECT_TRUE(hash_set.add("o", "o"));
  EXPECT_TRUE(hash_set.add("p", "p"));
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
