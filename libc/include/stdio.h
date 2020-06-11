#ifndef _STDIO_H
#define _STDIO_H 1
 
#include <sys/cdefs.h>
 
#include <stddef.h>
 
__BEGIN_DECLS

int printf(const char *format, ...);
int snprintf(char *buffer, int size, const char *format, ...);

__END_DECLS
 
#endif
