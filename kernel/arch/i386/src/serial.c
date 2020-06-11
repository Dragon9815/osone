#include "serial.h"

#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#include <sys/io.h>

#define COM1    0x3F8

enum
{
    REG_DATA             = 0,
    REG_INTERRUPT_ENABLE = 1,
    REG_FIFO_CONTROL     = 2,
    REG_LINE_CONTROL     = 3,
    REG_MODEM_CONTROL    = 4,
    REG_LINE_STATUS      = 5,
    REG_MODEM_STATUS     = 6,
    REG_SCRATCH          = 7,
};

#define REG_DLAB_LO REG_DATA
#define REG_DLAB_HI REG_INTERRUPT_ENABLE

static void writeRegister( uint16_t serial_port, uint8_t reg, uint8_t data )
{
    outb( data, serial_port + reg );
}

static uint8_t readRegister( uint16_t serial_port, uint8_t reg )
{
    return inb( serial_port + reg );
}

static int set_baudrate( uint16_t baudrate )
{
    uint8_t lineControl;
    uint16_t divisor;
    uint8_t divisor_lo;
    uint8_t divisor_hi;

    lineControl = readRegister( COM1, REG_LINE_CONTROL );
    lineControl |= 0x80; // Set DLAB to 1 to allow access to Baudrate registers
    writeRegister( COM1, REG_LINE_CONTROL, lineControl );

    divisor = 115200 / baudrate;
    if( divisor == 0 )
    {
        // TODO: set errno
        return -1;
    }

    divisor_lo = divisor & 0xFF;
    divisor_hi = ( divisor >> 8 ) & 0xFF;

    writeRegister( COM1, REG_DLAB_LO, divisor_lo );
    writeRegister( COM1, REG_DLAB_HI, divisor_hi );

    lineControl = readRegister( COM1, REG_LINE_CONTROL );
    lineControl &= 0x7F; // Set DLAB to 0 to allow access to data and interrupt enable registers
    writeRegister( COM1, REG_LINE_CONTROL, lineControl );

    return 0;
}

int serial_init( uint32_t baudrate, serial_databits_t dataBits, serial_stopbits_t stopBits, serial_parity_t parity )
{
    int result;

    result = set_baudrate( baudrate );
    if( result < 0 )
        return result;

    uint8_t lineControl = 0x00;

    switch( dataBits )
    {
    case SERIAL_DATABITS_5: lineControl |= 0x00; break;
    case SERIAL_DATABITS_6: lineControl |= 0x01; break;
    case SERIAL_DATABITS_7: lineControl |= 0x02; break;
    case SERIAL_DATABITS_8: lineControl |= 0x03; break;
    }

    switch( stopBits )
    {
    case SERIAL_STOPBITS_1: lineControl |= 0x00; break;
    case SERIAL_STOPBITS_2: lineControl |= 0x04; break;
    }

    switch( parity )
    {
    case SERIAL_PARITY_NONE:  lineControl |= 0x00; break;
    case SERIAL_PARITY_ODD:   lineControl |= 0x08; break;
    case SERIAL_PARITY_EVEN:  lineControl |= 0x18; break;
    case SERIAL_PARITY_MARK:  lineControl |= 0x28; break;
    case SERIAL_PARITY_SPACE: lineControl |= 0x38; break;
    }

    writeRegister( COM1, REG_LINE_CONTROL, lineControl );

    uint8_t fifoControl = 0xC7; // Enable FIFO, clear FIFO, 14-byte threshold
    writeRegister( COM1, REG_FIFO_CONTROL, fifoControl );

    uint8_t interruptEnable = 0;
    writeRegister( COM1, REG_INTERRUPT_ENABLE, interruptEnable );

    return 0;
}

static int isTransmitEmpty( uint16_t serial_port )
{
    return inb( serial_port + REG_LINE_STATUS ) & 0x20;
}

void serial_sendByte( uint8_t byte )
{
    while( isTransmitEmpty( COM1 ) == 0 );

    outb( byte, COM1 + REG_DATA );
}

void serial_sendByteArray( uint8_t * bytes, size_t count )
{
    for( size_t i = 0;i < count; i++ )
    {
        serial_sendByte( bytes[ i ] );
    }
}

void serial_sendString( const char * str )
{
    int len = strnlen( str, 10000 ); // limit string to 10000 characters
    serial_sendByteArray( (uint8_t *)str, len );
}