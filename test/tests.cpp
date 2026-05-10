// Copyright 2021 GHA Test Team
#include <gtest/gtest.h>
#include <cstdlib>
#include <vector>
#include <string>
#include "textgen.h"

TEST(TestGenTests, FirstPrefix) {
  std::vector<std::string> words = {"cat", "dog", "fish", "pig"};
  statetab stab;
  prefix firstPref;
  createTable(words, stab, firstPref);
  ASSERT_EQ(firstPref.size(), static_cast<size_t>(NPREF));
  EXPECT_EQ(firstPref[0], "cat");
  EXPECT_EQ(firstPref[1], "dog");
}

TEST(TestGenTests, PrefixCountThree) {
  prefix pref;
  pref.push_back("cat");
  pref.push_back("dog");
  pref.push_back("fish");
  ASSERT_EQ(pref.size(), 3);
  EXPECT_EQ(pref[0], "cat");
  EXPECT_EQ(pref[1], "dog");
  EXPECT_EQ(pref[2], "fish");
}

TEST(TestGenTests, PrefixSuffix) {
  std::vector<std::string> words = { "I", "go", "home" };
  statetab stab;
  prefix firstPref;
  createTable(words, stab, firstPref);
  prefix key = { "I", "go" };
  auto it = stab.find(key);
  ASSERT_NE(it, stab.end());
  EXPECT_EQ(it->second[0], "home");
}

TEST(TestGenTests, UniqueSuffixText) {
  statetab stab;
  prefix firstPref = { "I", "go" };
  stab[firstPref].push_back("home");
  std::srand(42);
  std::string generated = generateText(stab, firstPref, 3);
  EXPECT_EQ(generated, "I go home");
}

TEST(TextGenTest, UniqueSuffix) {
  statetab stab;
  prefix firstPref = {"I", "go"};
  stab[firstPref].push_back("home");
  auto it = stab.find(firstPref);
  ASSERT_NE(it, stab.end());
  EXPECT_EQ(it->second.size(), 1u);
  EXPECT_EQ(it->second[0], "home");
}

TEST(TextGenTest, MultipleSuffix) {
  statetab stab;
  prefix firstPref = { "one", "two" };
  stab[firstPref].push_back("three");
  stab[firstPref].push_back("four");
  stab[firstPref].push_back("five");
  std::srand(1);
  std::string generated = generateText(stab, firstPref, 3);
  std::string suffix = generated.substr(8);
  EXPECT_TRUE(suffix == "three" || suffix == "four" || suffix == "five");
}

TEST(TextGenTest, GeneratedTextLengthTen) {
  std::vector<std::string> words = { "a", "b", "c", "d", "e", "f",
      "g", "h", "i", "j", "k" };
  statetab stab;
  prefix firstPref;
  createTable(words, stab, firstPref);
  int maxgen = 10;
  std::string generated = generateText(stab, firstPref, maxgen);
  int wordCount = 1;
  for (char c : generated) {
      if (c == ' ') wordCount++;
  }
  EXPECT_EQ(wordCount, maxgen);
}

TEST(TextGenTest, GenerateTextZeroMaxgen) {
  statetab stab;
  prefix firstPref = { "I", "go" };
  stab[firstPref].push_back("home");
  std::string gen = generateText(stab, firstPref, 0);
  EXPECT_TRUE(gen.empty());
}

TEST(TextGenTest, EmptyStatetab) {
  statetab stab;
  prefix first = { "one", "two" };
  std::string gen = generateText(stab, first, 10);
  EXPECT_EQ(gen, "one two");
}

TEST(TextGenTest, CreateTableTwoWords) {
  std::vector<std::string> words = { "one", "two" };
  statetab stab;
  prefix firstPref;
  createTable(words, stab, firstPref);
  EXPECT_TRUE(stab.empty());
  EXPECT_FALSE(firstPref.empty());
  EXPECT_EQ(firstPref.size(), static_cast<size_t>(NPREF));
}

TEST(TestGenTests, GenerateOneWord) {
  statetab stab;
  prefix firstPref = { "I", "go" };
  stab[firstPref].push_back("home");
  std::string generated = generateText(stab, firstPref, 1);
  EXPECT_EQ(generated, "I go");
}
