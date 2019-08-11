//
// Created by User on 10/8/2019.
//

#include "../Library/Measurements.h"
#include <gtest/gtest.h>
#include <time.h>

TEST(MeasurementsClassTesting, Copy)
{
    Measurements m1 = Measurements();

    for (int i = 0; i < 100; i++) {
        m1.AddMeasurement(time(NULL),i);
    }

    Measurements m2 = Measurements(m1);

    ASSERT_EQ(m2.GetAccessVector().size(), 100);
    for (int i = 0; i < 100; i++) {
        ASSERT_EQ(m2.GetAccessVector()[i].clockCycles, i);
    }

    m1.SetInCacheTime(25);
    m1.SetNoCacheTime(75);
    m1.UpdateSpeculations();

    ASSERT_NE(m1.GetAccessVector()[20].speculatedCache, m2.GetAccessVector()[20].speculatedCache);
}

TEST(MeasurementsClassTesting, UpdateSpeculations)
{
    Measurements mida = Measurements();

    mida.UpdateSpeculations();

    for (int i = 0; i < 100; i++) {
        mida.AddMeasurement(time(NULL),i);
    }

    mida.SetInCacheTime(25);
    mida.SetNoCacheTime(75);

    for (int i = 0; i < 100; i++) {
        if (i <= 50)
            ASSERT_EQ(mida.GetAccessVector()[i].speculatedCache, Cache::L3);
        else
            ASSERT_EQ(mida.GetAccessVector()[i].speculatedCache, Cache::Memory);
    }

    mida.SetInCacheTime(80);
    mida.SetNoCacheTime(80);

    for (int i = 0; i < 100; i++) {
        if (i <= 80)
            ASSERT_EQ(mida.GetAccessVector()[i].speculatedCache, Cache::L3);
        else
            ASSERT_EQ(mida.GetAccessVector()[i].speculatedCache, Cache::Memory);
    }
}