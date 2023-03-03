#ifndef _ARG__H
#define _ARG__H
/**
 * Variadic list type.
 * 
 * Used by va_* macros.
 */
typedef __builtin_va_list va_list;
#define va_start __builtin_va_start // Macro for __builtin_va_start
#define va_end __builtin_va_end // Macro for __builtin_va_end
#define va_copy __builtin_va_copy // Macro for __builtin_va_copy
#define va_arg __builtin_va_arg // Macro for __builtin_va_arg

#endif //_ARG__H