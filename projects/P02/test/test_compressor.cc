#include <gtest/gtest.h>

extern "C" {
#include "compressor.h"
}

TEST(DeltaEnc, BasicOk)
{
    ASSERT_EQ(true,true);
}

TEST(DeltaEnc, BasicFail)
{
    ASSERT_EQ(false,true);
}