#include <gtest/gtest.h>

#include <YosysUtils.hpp>

TEST(WriteFirrtlTest, ErrorWithInvalidFileName) {
  auto result = YosysUtils::writeFirrtl("incorrect_filename.v", "aaa",
                                        "../../test/test_data/optimization_utils");
  std::string errorText =
      "Incorrect write_firrtl: ERROR: "
      "Can't open input file `incorrect_filename.v' for reading: "
      "No such file or directory\n\n";
  std::string errorResult = result.commandsOutput["error"];

  EXPECT_EQ(errorResult, errorText);
}

TEST(WriteFirrtlTest, ErrorWithInvalidFilePath) {
  auto result = YosysUtils::writeFirrtl("correct_filename.v", "aaa",
                                        "incorrect_filepath");
  std::string errorText =
      "Something went wrong during files parsing "
      "in YosysUtils: \nsh: 1: cd: can't cd to incorrect_filepath\n";
  std::string errorResult = result.commandsOutput["error"];
  EXPECT_EQ(errorResult, errorText);
}