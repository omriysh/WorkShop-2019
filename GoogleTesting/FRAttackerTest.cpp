//
// Created by User on 10/8/2019.
//

#include "../Library/FRAttacker.h"
#include <gtest/gtest.h>

TEST(FRAttackerClassTesting, Configure) {
    FRAttacker attacker = FRAttacker();

    ASSERT_THROW(attacker.Configure(), logic_error);

    // loading target manually
    Victim victor = Victim("/mnt/c/Users/User/Documents/Arazim/Workshop/WorkShop-2019/GoogleTesting/test.txt");
    victor.LoadFile();
    char data[] = {'w', 'o', 'w'};
    attacker.SetTarget(victor.FindInFile(data, 3));

    ASSERT_NO_THROW(attacker.Configure());
}