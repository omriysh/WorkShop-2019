//
// Created by User on 10/8/2019.
//

#include "../Library/Victim.h"
#include <gtest/gtest.h>

TEST(VictimClassTesting, FindInFile)
{
    Victim victor = Victim("/mnt/c/Users/User/Documents/Arazim/Workshop/WorkShop-2019/GoogleTesting/test.txt");
    victor.LoadFile();

    char* result = nullptr;
    char search1[] = {'w', 'o', 'w'};
    char search2[] = {'h', 'o', 'u', 's', 'e'};

    result = victor.FindInFile(search1, 3);
    ASSERT_NE(result, nullptr);
    ASSERT_EQ(*result, 'w');
    ASSERT_EQ(*(result+1), 'o');
    ASSERT_EQ(*result, 'w');

    result = victor.FindInFile(search2, 5);
    ASSERT_EQ(result, nullptr);
}