#include <gtest/gtest.h>

#include "Scanner.hpp"

namespace {

TEST(SCANNER_TESTS, Create_Scanner_from_inputs) {
    std::string input = "var car = \"blue\"";

    EXPECT_NO_THROW(auto scan = Scanner(input));
}

TEST(SCANNER_TESTS, ScanToken_Test) {
    std::string input = "var car = \"blue\"";

    auto scan = Scanner(input);

    EXPECT_NO_THROW(scan.ScanTokens());
}
} // namespace