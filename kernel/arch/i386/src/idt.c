#include "idt.h"

struct idt_descriptor
{
    u16 offset_lo;
    u16 selector;
    u8  reserved0;
    u8  type_attr;
    u16 offset_hi;
} PACKED_ATTRIB;
typedef struct idt_descriptor idt_descriptor_t;

struct idt_register
{
    u16 size;
    u32 offset;
} PACKED_ATTRIB;
typedef struct idt_register idt_register_t;

// base attribute definitions
#define IDT_DESC_P_Msk    0x80
#define IDT_DESC_P_Pos    7

#define IDT_DESC_DPL_Msk  0x70
#define IDT_DESC_DPL_Pos  4

#define IDT_DESC_S_Msk    0x08
#define IDT_DESC_S_Pos    3

#define IDT_DESC_TYPE_Msk 0x07
#define IDT_DESC_TYPE_Pos 0

// human readable definitions
#define IDT_DESC_PRESENT IDT_DESC_P_Msk

#define IDT_DESC_DPL_0 (0 << IDT_DESC_DPL_Pos)
#define IDT_DESC_DPL_1 (1 << IDT_DESC_DPL_Pos)
#define IDT_DESC_DPL_2 (2 << IDT_DESC_DPL_Pos)
#define IDT_DESC_DPL_3 (3 << IDT_DESC_DPL_Pos)

#define IDT_DESC_S_INT_OR_TRAP 0x00
#define IDT_DESC_S_TASK        IDT_DESC_S_Msk

#define IDT_DESC_TYPE_32BIT_TASK  0x05
#define IDT_DESC_TYPE_16BIT_INT   0x06
#define IDT_DESC_TYPE_16BIT_TRAP  0x07
#define IDT_DESC_TYPE_32BIT_INT   0x0E
#define IDT_DESC_TYPE_32BIT_TRAP  0x0F


void idt_add_descriptor(int num, u32 offset, u16 selector, u32 attrib_type)
{
    
}

kresult_t idt_init(u16 code_seclector)
{

}