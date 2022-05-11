#include <stdio.h>
#include <stdarg.h>
void HIP_Assert(const char *format, ...)
{
    va_list arglist;

    printf("Error: ");
    va_start(arglist, format);
    vprintf(format, arglist);
    va_end(arglist);
}

#if defined(_DEBUG)
#define HIP_ASSERT(condition, msg)
#else
#define HIP_ASSERT(condition, msg, ...) \
    if (!condition)                     \
        HIP_Assert(msg, __VA_ARGS__);
#endif
