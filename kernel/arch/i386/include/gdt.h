#ifndef __ARCH_I386_GDT_H__
#define __ARCH_I386_GDT_H__

#include "ktypes.h"

#ifdef __cplusplus
extern "C" {
#endif

extern kresult_t gdt_init( void );

#ifdef __cplusplus
}
#endif

#endif /* __ARCH_I386_GDT_H__ */