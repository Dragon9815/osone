#ifndef __KERNEL_SERIAL_H__
#define __KERNEL_SERIAL_H__

#include <stdint.h>
#include <stddef.h>

typedef enum 
{
    SERIAL_DATABITS_5,
    SERIAL_DATABITS_6,
    SERIAL_DATABITS_7,
    SERIAL_DATABITS_8,
} serial_databits_t;

typedef enum 
{
    SERIAL_STOPBITS_1,
    SERIAL_STOPBITS_2,
} serial_stopbits_t;

typedef enum 
{
    SERIAL_PARITY_NONE,
    SERIAL_PARITY_ODD,
    SERIAL_PARITY_EVEN,
    SERIAL_PARITY_MARK,
    SERIAL_PARITY_SPACE,
} serial_parity_t;

extern int serial_init( uint32_t baudrate, serial_databits_t dataBits, serial_stopbits_t dtopBits, serial_parity_t parity );

extern void serial_sendByte( uint8_t byte );
extern void serial_sendByteArray( uint8_t * bytes, size_t count );
extern void serial_sendString( const char * str );

#endif /* __KERNEL_SERIAL_H__ */