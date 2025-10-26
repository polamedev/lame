#include <lame/utils/Event.h>

#include <CppUTest/TestHarness.h>

TEST_GROUP(EventTests)
{

    Event event;

    void setup()
    {
        Event_Init(&event);
    }

    void teardown()
    {
    }
};

TEST(EventTests, clearAfterCreate)
{
    CHECK_FALSE(Event_Check(&event));
}

TEST(EventTests, checkEventSet)
{
    Event_Set(&event);

    CHECK_TRUE(Event_Check(&event));
}

TEST(EventTests, checkEventClear)
{
    Event_Set(&event);
    Event_Clear(&event);

    CHECK_FALSE(Event_Check(&event));
}

TEST(EventTests, checkEventTakeAfterInit)
{
    CHECK_FALSE(Event_Take(&event));
}

TEST(EventTests, checkEventTakeAfterSetEvent)
{
    Event_Set(&event);
    CHECK_TRUE(Event_Take(&event));
}

TEST(EventTests, checkEventAfterTake)
{
    Event_Set(&event);
    Event_Take(&event);
    CHECK_FALSE(Event_Check(&event));
}
