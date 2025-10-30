cmake_minimum_required(VERSION 3.21)

# Основные настройки проекта
project(
    lame-mocks-tests
    VERSION 1.0.0
    DESCRIPTION
        "Lame mocks lib"
    LANGUAGES C CXX
)

message(STATUS "Включено тестирование библиотеки lame::drivers-mock")

enable_language(CXX)

# Используется фреймворк CppUTest для тестирования
find_package(CppUTest REQUIRED)

# Подключение cmake CTest для тестирования, добавляет определение BUILD_TESTING - 
# Подключение include(CTest) в целом не нужно, достаточно enable_testing() для того функционала, который используется
# include(CTest)
enable_testing()

add_executable(lame-mocks-tests 
    allTests.cpp
    PinMockTest.cpp
    PinMockSpyTest.cpp
)
target_link_libraries(lame-mocks-tests lame::mocks CppUTest::CppUTest CppUTest::CppUTestExt)
add_test(lame-mocks-tests lame-mocks-tests)
