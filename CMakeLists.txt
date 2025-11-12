cmake_minimum_required(VERSION 3.21)

# Основные настройки проекта
project(
    lame
    VERSION 1.0.0
    DESCRIPTION
        "Embedded lame lib"
    LANGUAGES C
)

# Определяем является ли текущий проектом верхнего уровня. Для fetch проектов, gitsubmodule или просто вложенных проектов это неверно
# string(COMPARE EQUAL "${CMAKE_SOURCE_DIR}" "${CMAKE_CURRENT_SOURCE_DIR}" is_top_level)
# Но в новых версиях 3.21 можно использовать ${PROJECT_IS_TOP_LEVEL}

# -----------------------------------------------------------------------------------------------------------------------------------
# Настройка сборки библиотеки
# -----------------------------------------------------------------------------------------------------------------------------------

# Опции сборки
option(LAME_BUILD_TESTS       "Build lame tests"            OFF)  # Нужно ли собирать тесты для библиотеки
option(LAME_BUILD_MOCKS       "Build  lame mocks lib"       OFF)  # Нужно ли собирать мок-объекты библиотеки

# Установка типа сборки
if(NOT CMAKE_BUILD_TYPE)
    # Установить переменную CMAKE_BUILD_TYPE и сохранить в кэше
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type")
    # Устанавливаем для CMAKE_BUILD_TYPE возможные значения, которые можно будет выбрать через cmake-gui
    set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
endif()


# Добавление суфикса в имя дебажной библиотеки, нужно чтобы установить различия в названии. Возможно от этого стоит отказаться
set(CMAKE_DEBUG_POSTFIX -dev)

# -----------------------------------------------------------------------------------------------------------------------------------
# Настройка таргета библиотеки
# -----------------------------------------------------------------------------------------------------------------------------------

# Интерфесная библиотека с общими инклудами
add_library(lame-interface INTERFACE)

# Библиотека lamesw - часто программная библиотека, которая не зависит от аппаратной реализации
add_library(lame-base STATIC)

# Добавление библиотеки
# Библиотека lame реализуется зависимые файлы от определенного порта
add_library(lame STATIC)


######   lame-interface    ######
target_include_directories(lame-interface INTERFACE
    include/lame/device
    include/lame/drivers
    include/lame/utils
)

######   lame-base    ######
# VERSION - Устанавливаем версию библиотеки из версии проекта
# SOVERSION - Версия совместимости - определяет версию API стоит изменять, когда меняется API, поведение или используемый интерфейс
set_target_properties(
    lame-base
    PROPERTIES VERSION ${PROJECT_VERSION}
               SOVERSION ${PROJECT_VERSION_MAJOR}
)

target_sources(lame-base
    PRIVATE 
    src/base/Event.c
)

target_include_directories(lame-base
    # Пути включения доступные только библиотеке
    PRIVATE 
    src/base 
    # Пути включения доступные самой библиотеке и пользователям
    PUBLIC
    # Используется выражения генератора
    # При сборке BUILD_INTERFACE заменится на include
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include> 
    # При установке INSTALL_INTERFACE заменится на католог включения при установки
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

target_link_libraries(lame-base PRIVATE lame-interface lame-config)


######   lame    ######

# VERSION - Устанавливаем версию библиотеки из версии проекта
# SOVERSION - Версия совместимости - определяет версию API стоит изменять, когда меняется API, поведение или используемый интерфейс
set_target_properties(
    lame
    PROPERTIES VERSION ${PROJECT_VERSION}
               SOVERSION ${PROJECT_VERSION_MAJOR}
)

target_sources(lame
    PRIVATE 
    src/dependent/SoftTimer.c
    src/dependent/Led.c
)


target_include_directories(lame
    # Пути включения доступные только библиотеке
    PRIVATE 
    src/dependent 
    include/lame/device
    include/lame/drivers
    include/lame/utils
)

target_link_libraries(lame PUBLIC lame-base lame-port PRIVATE lame-interface lame-config)

# -----------------------------------------------------------------------------------------------------------------------------------
# Добавление других таргетов
# -----------------------------------------------------------------------------------------------------------------------------------

# set(LAME_BUILD_TESTS ON)

if(LAME_BUILD_TESTS)
    # Для тестов необходимы моки объектов для этого установим переменную
    set(LAME_BUILD_MOCKS ON)
    # Также собираем тесты для моков
    set(LAME_BUILD_MOCKS_TESTS ON)
    enable_testing()
    add_subdirectory(tests)
endif()

if(LAME_BUILD_MOCKS)
    add_subdirectory(mocks)
endif()
