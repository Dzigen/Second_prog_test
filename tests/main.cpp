#include <gtest/gtest.h>

#include "save_test.h"
#include "showlineswithdigits_test.h"

int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
