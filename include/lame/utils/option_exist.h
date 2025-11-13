#pragma once

// Макрос возвращает второй аргумент
#define SECOND_ARG(x1,x2,...) x2
#define CONCAT2(x1,x2) x1 ## x2

// Некоторая магия макросов. 
// ~ - обозначает пустой аргумент, если определен в начале
// и повторяет последний аргумент если определен после него 
#define OPTION_EXIST_VAL_ ~,1
#define OPTION_EXIST_VAL_0 ~,0
#define OPTION_EXIST_VAL_1 ~,1
#define OPTION_EXIST_IMPL(...) SECOND_ARG(__VA_ARGS__)

/**
 * @brief  Макрос проверяет наличие определение опции X
 * @return 1 - Если опция определена без значения или если опция определена с другими значениями
 *         0 - Если опция не определена или определена со значением отличного от 1 (0, 2, 3 ...) 
 */
#define OPTION_EXIST(x) OPTION_EXIST_IMPL(CONCAT2(OPTION_EXIST_VAL_,x), 0, ~)
