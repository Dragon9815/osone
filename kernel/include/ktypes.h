#ifndef __KERNEL_KTYPES_H__
#define __KERNEL_KTYPES_H__

#include <stdint.h>
#include <stdbool.h>

typedef int8_t i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

#ifdef __cplusplus
extern "C" {
#endif

typedef enum 
{
    K_ERROR = -1,
    K_OK = 0
} kresult_t;

#ifdef __cplusplus
}
#endif

#endif /* __KERNEL_KTYPES_H__ */