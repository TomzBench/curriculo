/* SPDX-License-Identifier: GPL-2.0 */
#ifndef CURRICULO_PLATFORM_COMMON_MACROS_H
#define CURRICULO_PLATFORM_COMMON_MACROS_H

#include <stddef.h>

/**
 * PAL_CONTAINER_OF - cast a member of a structure out to the containing
 *                    structure
 * @ptr:    the pointer to the member.
 * @type:   the type of the container struct this is embedded in.
 * @member: the name of the member within the struct.
 */
#define PAL_CONTAINER_OF(ptr, type, member)                                    \
  ((type *)((char *)(ptr) - offsetof(type, member)))

/**
 * PAL_NUM_VA_ARGS - count the number of variadic arguments
 *
 * Supports 1-16 arguments. Does not work with 0 arguments.
 * Adapted from Zephyr RTOS (include/zephyr/sys/util_macro.h)
 */
#define PAL_NUM_VA_ARGS(...)                                                   \
  PAL_NUM_VA_ARGS_IMPL(                                                        \
      __VA_ARGS__, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0)
#define PAL_NUM_VA_ARGS_IMPL(_1,                                               \
                             _2,                                               \
                             _3,                                               \
                             _4,                                               \
                             _5,                                               \
                             _6,                                               \
                             _7,                                               \
                             _8,                                               \
                             _9,                                               \
                             _10,                                              \
                             _11,                                              \
                             _12,                                              \
                             _13,                                              \
                             _14,                                              \
                             _15,                                              \
                             _16,                                              \
                             N,                                                \
                             ...)                                              \
  N

#endif /* CURRICULO_PLATFORM_COMMON_MACROS_H */
