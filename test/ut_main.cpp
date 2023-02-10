#include <gtest/gtest.h>
#include "./Device/ut_gateAnd.h"
#include "./Device/ut_gateNot.h"
#include "./Device/ut_gateOR.h"
#include "./Device/ut_iPin.h"
#include "./Device/ut_oPin.h"
#include "./ut_LogicSimulator.h"

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}