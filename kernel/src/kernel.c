#include "platform.h"

#include <stdbool.h>
#include <stdint.h>

#include <serial.h>

uint16_t * VIDMEM = ((uint16_t *)0xB8000);

void kernel_main( void )
{
    VIDMEM[  0 ] = ( 0x7A << 8 ) | 'H';
    VIDMEM[  1 ] = ( 0x7A << 8 ) | 'e';
    VIDMEM[  2 ] = ( 0x7A << 8 ) | 'l';
    VIDMEM[  3 ] = ( 0x7A << 8 ) | 'l';
    VIDMEM[  4 ] = ( 0x7A << 8 ) | 'o';
    VIDMEM[  5 ] = ( 0x7A << 8 ) | ',';
    VIDMEM[  6 ] = ( 0x7A << 8 ) | ' ';
    VIDMEM[  7 ] = ( 0x7A << 8 ) | 'W';
    VIDMEM[  8 ] = ( 0x7A << 8 ) | 'o';
    VIDMEM[  9 ] = ( 0x7A << 8 ) | 'r';
    VIDMEM[ 10 ] = ( 0x7A << 8 ) | 'l';
    VIDMEM[ 11 ] = ( 0x7A << 8 ) | 'd';
    VIDMEM[ 12 ] = ( 0x7A << 8 ) | '!';

    serial_init( 115200, SERIAL_DATABITS_8, SERIAL_STOPBITS_1, SERIAL_PARITY_NONE );

    serial_sendString( "Hello, World!\n\r" );

    gdt_init( );

    volatile int x = 10;
    volatile int z = 0;
    volatile int y = x / z;

    (void)y;

    serial_sendString( "WTF\n\r" );

    while( true )
    {
        // serial_sendByte( '+' );
    }
}
