#ifndef __TYPES_H__
#define __TYPES_H__

#include <stdint.h>

typedef enum
{
    CPPEVT_OK = 0,
    CPPEVT_ERROR,
    CPPEVT_NOT_FOUND,
    CPPEVT_EXCEED_RANGE
} status_t;

#endif