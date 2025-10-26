cmake_minimum_required(VERSION 3.21)

# Основные настройки проекта
project(
    lame
    VERSION 1.0.0
    DESCRIPTION
        "Tests for embedded lame lib"
    LANGUAGES C CXX
)

# Используется фреймворк CppUTest для тестирования
find_package(CppUTest REQUIRED)

# Подключение cmake CTest для тестирования, добавляет определение BUILD_TESTING - 
# Подключение include(CTest) в целом не нужно, достаточно enable_testing() для того функционала, который используется
# include(CTest)
enable_testing()

add_executable(lame-tests 
    allTests.cpp
    utils/EventTest.cpp
)
target_link_libraries(lame-tests   lame::lame CppUTest::CppUTest CppUTest::CppUTestExt)
add_test(lame-tests   lame-tests )
