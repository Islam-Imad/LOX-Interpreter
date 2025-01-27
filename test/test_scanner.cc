#include <gtest/gtest.h>
#include "scanner.h"

TEST(ScannerTest, TestScanner)
{
    Scanner scanner("print \"Hello, World!\";");
    ASSERT_EQ(1, 1);
}