#include <lame/utils/Event.h>

#include <CppUTest/TestHarness.h>

TEST_GROUP(EventTests) {

LAME_Event event;

void setup()
{
    LAME_Event_Init(&event);
}

void teardown()
{
}

};

TEST(EventTests, clearAfterCreate)
{
    CHECK_FALSE(LAME_Event_Check(&event));
}

TEST(EventTests, checkEventSet)
{
    LAME_Event_Set(&event);

    CHECK_TRUE(LAME_Event_Check(&event));
}

TEST(EventTests, checkEventClear)
{
    LAME_Event_Set(&event);
    LAME_Event_Clear(&event);

    CHECK_FALSE(LAME_Event_Check(&event));
}

TEST(EventTests, checkEventTakeAfterInit)
{
    CHECK_FALSE(LAME_Event_Take(&event));
}

TEST(EventTests, checkEventTakeAfterSetEvent)
{
    LAME_Event_Set(&event);
    CHECK_TRUE(LAME_Event_Take(&event));
}

TEST(EventTests, checkEventAfterTake)
{
    LAME_Event_Set(&event);
    LAME_Event_Take(&event);
    CHECK_FALSE(LAME_Event_Check(&event));
}
