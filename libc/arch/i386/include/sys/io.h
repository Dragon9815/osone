#ifndef __SYS_IO_H__
#define __SYS_IO_H__

#include <sys/cdefs.h>

__BEGIN_DECLS

static __inline unsigned char
inb ( unsigned short int __port )
{
    unsigned char _v;

   __asm__ volatile ( "inb %w1,%0" : "=a" (_v) : "Nd" (__port) );
   return _v;
}

static __inline void
outb ( unsigned short int __value, unsigned short int __port )
{
   __asm__ volatile ( "outb %b0,%w1" : : "a" (__value), "Nd" (__port) );
}

__END_DECLS

#endif /* __SYS_IO_H__ */