#ifndef _TYPES__H // Header guard
#define _TYPES__H

// Types

/**
 * 8 bit integer.
 * 
 * Alias for char.
 */
typedef char int8_t; 

/**
 * 8 bit unsigned integer.
 * 
 * Alias for unsigned char.
 */
typedef unsigned char uint8_t; 

/**
 * 16 bit integer.
 * 
 * Alias for short.
 */
typedef short int16_t; 
/**
 * 16 bit unsigned integer.
 * 
 * Alias for unsigned short.
 */
typedef unsigned short uint16_t; 

/**
 * 32 bit integer.
 * 
 * Alias for long.
 */
typedef long int32_t; 
/**
 * 32 bit unsigned integer.
 * 
 * Alias for unsigned long.
 */
typedef unsigned long uint32_t;

/**
 * 64 bit integer.
 * 
 * Alias for long long.
 */
typedef long long int64_t;
/**
 * 64 bit unsigned integer.
 * 
 * Alias for unsigned long long.
 */
typedef unsigned long long uint64_t;

// Sizes

#define INT8_MAX 127 // Maximum size of int8_t
#define INT8_MIN -128 // Minimum size of int8_t

#define UINT8_MAX 255 // Maximum size of uint8_t
#define UINT8_MIN 0 // Minimum size of uint8_t

#define INT16_MAX 32767 // Maximum size of int16_t
#define INT16_MIN -32768 // Minimum size of int16_t

#define UINT16_MAX 65535 // Maximum size of uint16_t
#define UINT16_MIN 0 // Minimum size of uint16_t

#define INT32_MAX 2147483647 // Maximum size of int32_t
#define INT32_MIN -2147483648 // Minimum size of int32_t

#define UINT32_MAX 4294967295 // Maximum size of uint32_t
#define UINT32_MIN 0 // Minimum size of uint32_t

#define INT64_MAX 9223372036854775807 // Maximum size of int64_t
#define INT64_MIN -9223372036854775808 // Minimum size of int64_t

#define UINT64_MAX 18446744073709551615 // Maximum size of uint64_t
#define UINT64_MIN 0 // Minimum size of uint64_t

#endif // _TYPES__H