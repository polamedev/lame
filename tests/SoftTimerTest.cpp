#include <lame/utils/SoftTimer.h>

#include <lame/mocks/timeServiceMock.hpp>

#include <CppUTest/TestHarness.h>

TEST_GROUP(SoftTimer)
{
    SoftTimer tim;

    void setup()
    {
        SoftTimer_Init(&tim, SoftTimer_ModePeriodic, 100);
    }

    void teardown()
    {
        millis_set(0);
    }
};

TEST(SoftTimer, stopAfterInit)
{
    CHECK_TRUE(SoftTimer_GetState(&tim) == SoftTimer_StateStop);
}

TEST(SoftTimer, runAfterStart)
{
    SoftTimer_Start(&tim);
    CHECK_TRUE(SoftTimer_GetState(&tim) == SoftTimer_StateRun);
}

TEST(SoftTimer, notOccurredAfterStart)
{
    SoftTimer_Start(&tim);
    CHECK_TRUE(SoftTimer_Occur(&tim) == false);
}

TEST(SoftTimer, timerOccurred)
{
    SoftTimer_Start(&tim);
    millis_set(100);

    CHECK_TRUE(SoftTimer_Occur(&tim) == true);
}

TEST(SoftTimer, SecondCheckAfterOccurred)
{
    SoftTimer_Start(&tim);
    millis_set(100);
    SoftTimer_Occur(&tim);
    CHECK_TRUE(SoftTimer_Occur(&tim) == false);
}
