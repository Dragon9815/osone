#ifndef _STRING_H
#define _STRING_H 1
 
#include <sys/cdefs.h>
 
#include <stddef.h>
 
__BEGIN_DECLS
 
int    memcmp ( const void * s1, const void * s2, size_t count );
void * memcpy ( void * __restrict dest, const void* __restrict src, size_t count );
void * memmove( void * dest, const void * src, size_t count );
void * memset ( void * s, int value, size_t count );

size_t strlen ( const char * str );
size_t strnlen( const char * str, size_t maxlen );

__END_DECLS
 
#endif
