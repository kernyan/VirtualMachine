#include "gtest/gtest.h"
#include "parser.h"

TEST(parser, first_token)
{
  std::string s = "parser these tokens\r";
  size_t i = 0;
  size_t j = 0;
  VMParser::find_token(s, size_t (0), i, j);
  EXPECT_EQ(i, 0);
  EXPECT_EQ(j, 6);
  EXPECT_EQ(s.substr(i, j-i), "parser");
}

TEST(parser, series_of_token)
{
  std::string s = "parser these tokens\r";
  vector<std::string> v;
  size_t i = 0;
  size_t j = 0;
  while (VMParser::find_token(s, j, i, j)) {
    v.push_back(s.substr(i, j-i));
  }
  EXPECT_EQ(v[0], "parser");
  EXPECT_EQ(v[1], "these");
  EXPECT_EQ(v[2], "tokens");
}

int main(int argc, char *argv[])
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
