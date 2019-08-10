//
// Created by User on 10/8/2019.
//

#include "../Library/PPAttacker.h"
#include <gtest/gtest.h>

TEST(PPAttackerClassTesting, Configure) {
    PPAttacker attacker = PPAttacker();

    ASSERT_NO_THROW(attacker.Configure());
}

