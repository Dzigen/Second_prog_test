#include <gtest/gtest.h>

#include "save_test.h"
#include "showlineswithdigits_test.h"
#include "c1n_test.h"
#include "m_test.h"
#include "mle_test.h"
int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
