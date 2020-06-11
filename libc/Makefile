BUILDDIR := build
SRCDIR := src

CC ?= clang
CXX ?= clang++
LD ?= $(HOST)-ld
AS ?= nasm
AR ?= $(HOST)-ar

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
CPPFLAGS := $(CPPFLAGS) -D__is_libc -Iinclude
ASFLAGS := $(ASFLAGS)
LIBK_CFLAGS := $(CFLAGS)
LIBK_CPPFLAGS := $(CPPFLAGS) -D__is_libk
LIBK_ASFLAGS := $(ASFLAGS)

ARCHDIR := arch/$(HOSTARCH)
include $(ARCHDIR)/arch.mk

CFLAGS := $(CFLAGS) $(ARCH_CFLAGS)
CPPFLAGS := $(CPPFLAGS) -I$(ARCHDIR)/include $(ARCH_CPPFLAGS)
ASFLAGS := $(ASFLAGS) $(ARCH_ASFLAGS)
LIBK_CFLAGS := $(CFLAGS) $(KERNEL_ARCH_CFLAGS)
LIBK_CPPFLAGS := $(CPPFLAGS) $(KERNEL_ARCH_CPPFLAGS)

FREESRCS=\
$(ARCH_FREESRCS) \
$(SRCDIR)/stdio/printf.c \
$(SRCDIR)/stdio/putchar.c \
$(SRCDIR)/stdio/puts.c \
$(SRCDIR)/stdlib/abort.c \
$(SRCDIR)/string/memcmp.c \
$(SRCDIR)/string/memcpy.c \
$(SRCDIR)/string/memmove.c \
$(SRCDIR)/string/memset.c \
$(SRCDIR)/string/strlen.c \
$(SRCDIR)/string/strnlen.c \

HOSTEDSRCS=\
$(ARCH_HOSTEDSRCS) \

FREEOBJS = $(addprefix $(BUILDDIR)/,$(addsuffix .o, $(basename $(FREESRCS))))
HOSTEDOBJS = $(addprefix $(BUILDDIR)/,$(addsuffix .o, $(basename $(HOSTEDSRCS))))

FREEDEPS=$(addprefix $(BUILDDIR)/,$(addsuffix .d, $(basename $(filter %.c,$(FREESRCS)))))
HOSTEDDEPS=$(addprefix $(BUILDDIR)/,$(addsuffix .d, $(basename $(filter %.c,$(HOSTEDSRCS)))))
DEPS=$(FREEDEPS) $(HOSTEDDEPS)

OBJS=\
$(FREEOBJS)\
$(HOSTEDOBJS)\

LIBK_OBJS = $(FREEOBJS:.o=.libk.o)

# no libc yet
BINARIES = libk.a

.PHONY: all clean install install-headers install-libs
all: $(BINARIES)

libc.a: $(OBJS)
	$(AR) rcs $@ $(OBJS)

libk.a: $(OBJS)
	$(AR) rcs $@ $(OBJS)

$(BUILDDIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) -MD -c $< -o $@ -std=gnu11 $(CFLAGS) $(CPPFLAGS)

$(BUILDDIR)/%.libk.o: %.c
	@mkdir -p $(dir $@)
	$(CC) -MD -c $< -o $@ -std=gnu11 $(LIBK_CFLAGS) $(LIBK_CPPFLAGS)

$(BUILDDIR)/%.o: %.asm
	@mkdir -p $(dir $@)
	$(AS) $(ASFLAGS) $< -o $@

$(BUILDDIR)/%.libk.o: %.asm
	@mkdir -p $(dir $@)
	$(AS) $(LIBK_ASFLAGS) $< -o $@


install: install-headers install-libs
	
install-libs: $(BINARIES)
	@mkdir -p $(DESTDIR)$(LIBDIR)
	cp $(BINARIES) $(DESTDIR)$(LIBDIR)

install-headers:
	@mkdir -p $(DESTDIR)$(INCLUDEDIR)
	cp -R --preserve=timestamps include/. $(DESTDIR)$(INCLUDEDIR)/.
	cp -R --preserve=timestamps $(ARCHDIR)/include/. $(DESTDIR)$(INCLUDEDIR)/.

clean:
	rm -rf $(BUILDDIR)
	rm -f $(BINARIES)

-include $(wildcard $(DEPS))
