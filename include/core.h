#pragma once

#include "types.h"

#ifndef NULL
#define NULL 0
#endif

#define offset(type, member) ((ptr_t)((char*)&(((type*)0)->member)))

#define new(type) ((type*)(malloc(sizeof(type))))



static unsigned short endian = 0x01;
#define __LITTLE_ENDIAN 1
#define __BIG_ENGIAN 0
#define __ENDIAN (((char*)&endian)[0])