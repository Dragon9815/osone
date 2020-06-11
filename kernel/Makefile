BUILDDIR := build

CC ?= clang
CXX ?= clang++
LD ?= $(HOST)-ld
AS ?= nasm

CFLAGS ?= -Og -g
CPPFLAGS ?=
LDFLAGS ?=
LIBS ?=

DESTDIR ?=
PREFIX ?= /usr/local
EXEC_PREFIX ?= $(PREFIX)
BOOTDIR ?= $(EXEC_PREFIX)/boot
INCLUDEDIR ?= $(PREFIX)/include

CFLAGS := $(CFLAGS) -ffreestanding -Wall -Wextra
CPPFLAGS := $(CPPFLAGS) -D__is_kernel -Iinclude
ASFLAGS := $(ASFLAGS)
LDFLAGS := $(LDFLAGS)
LIBS := $(LIBS) -nostdlib -lk 

ARCHDIR := arch/$(HOSTARCH)
include $(ARCHDIR)/arch.mk

CFLAGS := $(CFLAGS) $(KERNEL_ARCH_CFLAGS)
CPPFLAGS := $(CPPFLAGS) -I$(ARCHDIR)/include $(KERNEL_ARCH_CPPFLAGS)
ASFLAGS := $(ASFLAGS) $(KERNEL_ARCH_ASFLAGS)
LDFLAGS := $(LDFLAGS) $(KERNEL_ARCH_LDFLAGS)
LIBS := $(LIBS) $(KERNEL_ARCH_LIBS)

KERNEL_SRCS=\
$(KERNEL_ARCH_SRCS)\
src/kernel.c

KERNEL_OBJS=$(addprefix $(BUILDDIR)/,$(addsuffix .o, $(basename $(KERNEL_SRCS))))
KERNEL_DEPS=$(addprefix $(BUILDDIR)/,$(addsuffix .d, $(basename $(filter %.c,$(KERNEL_SRCS)))))

OBJS=\
$(BUILDDIR)/$(ARCHDIR)/src/crti.o\
$(KERNEL_OBJS)\
$(BUILDDIR)/$(ARCHDIR)/src/crtn.o

LINK_LIST=\
$(LDFLAGS)\
$(BUILDDIR)/$(ARCHDIR)/src/crti.o\
$(KERNEL_OBJS)\
$(LIBS)\
$(BUILDDIR)/$(ARCHDIR)/src/crtn.o

.PHONY: all clean install install-headers install-kernel install-grub
all: $(OSNAME)

$(OSNAME): $(OBJS) $(ARCHDIR)/kernel.ld
	$(LD) -T $(ARCHDIR)/kernel.ld -o $@ $(LDFLAGS) -Map $@.map $(LINK_LIST)
	$(OBJDUMP) -S -d $@ > $@.lst
	grub-file --is-x86-multiboot $@ 

$(BUILDDIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) -MD -c $< -o $@ -std=gnu11 $(CFLAGS) $(CPPFLAGS)

$(BUILDDIR)/%.o: %.asm
	@mkdir -p $(dir $@)
	$(AS) $(ASFLAGS) $< -o $@


install: install-headers install-kernel install-grub
	
install-kernel: $(OSNAME)
	@mkdir -p $(DESTDIR)$(BOOTDIR)
	cp $< $(DESTDIR)$(BOOTDIR)/

install-grub: grub.cfg
	@mkdir -p $(DESTDIR)$(BOOTDIR)/grub
	cp $< $(DESTDIR)$(BOOTDIR)/grub/

install-headers:
	@mkdir -p $(DESTDIR)$(INCLUDEDIR)
	cp -R --preserve=timestamps include/. $(DESTDIR)$(INCLUDEDIR)/.

clean:
	rm -rf $(BUILDDIR)
	rm -rf osone.kernel

-include $(wildcard $(KERNEL_DEPS))
