#ifndef __ARCH_I386_IDT_H__
#define __ARCH_I386_IDT_H__

#include "ktypes.h"

#ifdef __cplusplus
extern "C" {
#endif

extern kresult_t idt_init(u16 code_seclector);

#ifdef __cplusplus
}
#endif

#endif /* __ARCH_I386_IDT_H__ */