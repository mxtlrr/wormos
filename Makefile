CC := i386-elf-gcc
AS := nasm

CFLAGS := -ffreestanding -O2 -Wall -Wextra -Iinclude/

AFLAGS := -felf32 -Iinclude/

all: compile make_iso
.PHONY: all

override OFILES := $(shell find ./obj/ -type f -name '*.o')
override CFILES := $(shell find ./ -type f -name '*.c')

compile:
	mkdir -p obj/ bin/
	$(AS) $(AFLAGS) src/boot/boot.asm -o obj/boot.o
	$(AS) -felf32 -g include/arch/idt/_idt.asm -o obj/_idt.o
	@$(foreach file, $(CFILES), $(CC) $(CFLAGS) -c $(file) -o obj/$(basename $(notdir $(file))).o; echo CC $(file);)

	$(CC) -Tsrc/link.ld -o bin/os.bin -ffreestanding -O2 -nostdlib $(OFILES) -lgcc


make_iso:
	@mkdir -p isodir/boot/grub
	@cp bin/os.bin isodir/boot/os.bin
	@cp src/boot/grub.cfg isodir/boot/grub/grub.cfg
	@grub-mkrescue -o bin/worm-os.iso isodir


qemu: bin/worm-os.iso
	qemu-system-i386 -cdrom $^

clean: bin/worm-os.iso bin/ obj/ isodir/
	rm -rf $^