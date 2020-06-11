#include "gdt.h"
#include "kcc.h"

#define GDT_NUM_DESCRIPTORS 5

struct gdt_descriptor
{
    u16 limit_lo;
    u16 base_lo;
    u8  base_mid;
    u8  access;
    u8  limit_hi : 4;
    u8  flags : 4;
    u8  base_hi;
} PACKED_ATTRIB;
typedef struct gdt_descriptor gdt_descriptor_t;

struct gdt_register
{
    u16 size;
    u32 offset;
} PACKED_ATTRIB;
typedef struct gdt_register gdt_register_t;

// -------- Access Byte -------------------------------------------------------
#define GDT_ACCESS_ACCESSED_MASK    0x01    // 0000 0001
#define GDT_ACCESS_RW_MASK          0x02    // 0000 0010
#define GDT_ACCESS_DIR_CONFORM_MASK 0x04    // 0000 0100
#define GDT_ACCESS_EXECUTABLE_MASK  0x08    // 0000 1000
#define GDT_ACCESS_NSYSTEM_MASK     0x10    // 0001 0000
#define GDT_ACCESS_DPL_MASK         0x60    // 0110 0000
#define GDT_ACCESS_PRESENT_MASK     0x80    // 1000 0000

#define GDT_ACCESS_ACCESSED         0x01    // 0000 0001
#define GDT_ACCESS_RW               0x02    // 0000 0010
#define GDT_ACCESS_DIR_CONFORM      0x04    // 0000 0100
#define GDT_ACCESS_EXECUTABLE       0x08    // 0000 1000
#define GDT_ACCESS_NSYSTEM          0x10    // 0001 0000
#define GDT_ACCESS_DPL0             0x00    // 0000 0000
#define GDT_ACCESS_DPL1             0x20    // 0010 0000
#define GDT_ACCESS_DPL2             0x40    // 0100 0000
#define GDT_ACCESS_DPL3             0x60    // 0110 0000
#define GDT_ACCESS_PRESENT          0x80    // 1000 0000

// -------- Flags Nibble ------------------------------------------------------
#define GDT_FLAGS_SIZE_MASK         0x4     // 0100
#define GDT_FLAGS_GRAN_MASK         0x8     // 1000

#define GDT_FLAGS_SIZE_16BIT        0 
#define GDT_FLAGS_SIZE_32BIT        GDT_FLAGS_SIZE_MASK
#define GDT_FLAGS_GRAN_BYTE         0
#define GDT_FLAGS_GRAN_PAGE         GDT_FLAGS_GRAN_MASK

// -------- Defined Combinations ----------------------------------------------
#define GDT_ACCESS_CODE_RING0       (GDT_ACCESS_PRESENT | GDT_ACCESS_DPL0 | GDT_ACCESS_NSYSTEM | GDT_ACCESS_EXECUTABLE | GDT_ACCESS_RW)
#define GDT_ACCESS_DATA_RING0       (GDT_ACCESS_PRESENT | GDT_ACCESS_DPL0 | GDT_ACCESS_NSYSTEM | GDT_ACCESS_RW)
#define GDT_ACCESS_CODE_RING3       (GDT_ACCESS_PRESENT | GDT_ACCESS_DPL3 | GDT_ACCESS_NSYSTEM | GDT_ACCESS_EXECUTABLE | GDT_ACCESS_RW)
#define GDT_ACCESS_DATA_RING3       (GDT_ACCESS_PRESENT | GDT_ACCESS_DPL3 | GDT_ACCESS_NSYSTEM | GDT_ACCESS_RW)

#define GDT_FLAGS_COMMON            (GDT_FLAGS_GRAN_PAGE | GDT_FLAGS_SIZE_32BIT)

gdt_descriptor_t gdt[ GDT_NUM_DESCRIPTORS ];
gdt_register_t gdtr;

static void gdt_setup_descriptor( int num, u32 base, u32 limit, u8 flags, u8 access )
{
    if(num >= GDT_NUM_DESCRIPTORS) {
        return;
    }

    gdt[num].base_lo  = base & 0xFFFF;
    gdt[num].base_mid = (base >> 16) & 0xFF;
    gdt[num].base_hi  = (base >> 24) & 0xFF;

    gdt[num].limit_lo = limit & 0xFFFF;
    gdt[num].limit_hi = limit & 0xF;

    gdt[num].flags  = flags;
    gdt[num].access = access;
}

extern inline void gdt_flush( uint32_t gdtr );

kresult_t gdt_init( void )
{
    // null descriptor
    gdt_setup_descriptor( 0, 0, 0, 0, 0 );
    // kernel code descriptor
    gdt_setup_descriptor( 1, 0, 0xFFFFF, GDT_FLAGS_COMMON, GDT_ACCESS_CODE_RING0);
    // kernel data descriptor
    gdt_setup_descriptor( 2, 0, 0xFFFFF, GDT_FLAGS_COMMON, GDT_ACCESS_DATA_RING0);
    // user code descriptor
    gdt_setup_descriptor( 3, 0, 0xFFFFF, GDT_FLAGS_COMMON, GDT_ACCESS_CODE_RING3);
    // user data descriptor
    gdt_setup_descriptor( 4, 0, 0xFFFFF, GDT_FLAGS_COMMON, GDT_ACCESS_DATA_RING3);

    gdtr.offset = (uint32_t)gdt;
    gdtr.size = GDT_NUM_DESCRIPTORS * sizeof( gdt_descriptor_t ) - 1;

    gdt_flush( (uint32_t)&gdtr );
}
