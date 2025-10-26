#include <CppUTest/CommandLineTestRunner.h>
#include <CppUTest/TestRegistry.h>
#include <CppUTestExt/MockSupportPlugin.h>

int main(int argc, char **argv)
{
    printf("\nAll Drivers Mocks Tests");

    MockSupportPlugin mockPlugin;

    // Подключаем плагин mockSupport
    // Что позволит не вызывать mock().clear(); и mock().checkExpectations
    TestRegistry::getCurrentRegistry()->installPlugin(&mockPlugin);

    return RUN_ALL_TESTS(argc, argv);
}
