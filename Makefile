OSNAME := osone
DEFAULT_HOST := i686-elf

HOST := $(DEFAULT_HOST)
HOSTARCH != ./target-triplet-to-arch.sh $(HOST)

CC := clang
CXX := clang++
LD := $(HOST)-ld
AS := nasm
AR := $(HOST)-ar
OBJDUMP := $(HOST)-objdump

PREFIX := /usr
EXEC_PREFIX := /usr
BOOTDIR := /boot
LIBDIR := $(EXEC_PREFIX)/lib
INCLUDEDIR := $(PREFIX)/include

CFLAGS := -Og -g
CPPFLAGS := 

SYSROOT := $(shell pwd)/sysroot
DESTDIR := $(SYSROOT)

CC := $(CC) --sysroot=$(SYSROOT)
CXX := $(CXX) --sysroot=$(SYSROOT)
LD := $(LD) --sysroot=$(SYSROOT)

export

.PHONY: all build-all build-kernel build-libc clean-all clean-kernel clean-libc

all: $(OSNAME).iso

headers: headers-libc headers-kernel 
	
headers-kernel:
	@$(MAKE) -C kernel install-headers

headers-libc:
	@$(MAKE) -C kernel install-headers

build: build-libc build-kernel 

build-kernel:
	@$(MAKE) -C kernel install

build-libc:
	@$(MAKE) -C libc install

clean: clean-libc clean-kernel 
	rm -rf isodir
	rm -rf sysroot
	rm -rf $(OSNAME).iso

clean-kernel:
	@$(MAKE) -C kernel clean

clean-libc:
	@$(MAKE) -C libc clean

$(OSNAME).iso: build kernel/grub.cfg
	mkdir -p isodir/boot/grub
	cp $(SYSROOT)$(BOOTDIR)/$(OSNAME) isodir/boot/$(OSNAME)
	cp $(SYSROOT)$(BOOTDIR)/grub/grub.cfg isodir/boot/grub/grub.cfg
	grub-mkrescue -o $@ isodir

qemu: $(OSNAME).iso
	qemu-system-$(HOSTARCH) -cdrom $(OSNAME).iso -serial pty

qemu-debug: $(OSNAME).iso
	qemu-system-$(HOSTARCH) -cdrom $(OSNAME).iso -serial pty -S -gdb tcp::3333
