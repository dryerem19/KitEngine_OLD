/**
 * @file KitCore.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-12-15
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#pragma once
#include <cstdio>

#ifdef DEBUG
    #define DEBUG_ENABLE 1
#else
    #define DEBUG_ENABLE 0
#endif

#define DEBUG_MSG(fmt, ...)                                                 \
    do {                                                                    \
        if (DEBUG_ENABLE) {                                                 \
            fprintf(stdout, "[DEBUG] - %d:%s(): " fmt,                      \
                    __LINE__, __func__, __VA_ARGS__);                       \
            putchar('\n');                                                  \
        }                                                                   \
    } while(0)                                                              \

