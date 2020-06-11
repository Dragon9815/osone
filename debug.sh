#!/usr/bin/env bash
set -e

#qemu-system-i386 -cdrom osone.iso -serial pty -S -gdb tcp::3333&
#QEMU_PID=$!
#sleep 2

i686-elf-gdb -x init_gdb 
#kill $QEMU_PID
