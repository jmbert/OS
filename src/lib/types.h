#ifndef _TYPES__H // Header guard
#define _TYPES__H

// Types

typedef char int8_t;
typedef unsigned char uint8_t;

typedef short int16_t;
typedef unsigned short uint16_t;

typedef long int32_t;
typedef unsigned long uint32_t;

// DO NOT USE IN 32BIT MODE
typedef long long int64_t;
// DO NOT USE IN 32BIT MODE
typedef unsigned long long uint64_t;

// Sizes

#define INT8_MAX 127
#define INT8_MIN -128

#define UINT8_MAX 255
#define UINT8_MIN 0

#define INT16_MAX 32767
#define INT16_MIN -32768

#define UINT16_MAX 65535
#define UINT16_MIN 0

#define INT32_MAX 2147483647
#define INT32_MIN -2147483648

#define UINT32_MAX 4294967295
#define UINT32_MIN 0

#define INT64_MAX 9223372036854775807
#define INT64_MIN -9223372036854775808

#define UINT64_MAX 18446744073709551615
#define UINT64_MIN 0

#endif // _TYPES__H