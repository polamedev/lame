#include <lame/device/Led.h>

#include <CppUTest/TestHarness.h>

TEST_GROUP(LedTests)
{

    Led led;

    void setup()
    {
    }

    void teardown()
    {
    }
};

TEST(LedTests, clearAfterCreate)
{
    CHECK_TRUE(true);
}

// TODO Дописать тесты
