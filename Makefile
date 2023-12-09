CC := i386-elf-gcc
AS := nasm

CFLAGS := -ffreestanding -O2 -Wall -Wextra -Iinclude/ \
					-mgeneral-regs-only -g

AFLAGS := -felf32 -Iinclude/ -g


all: compile make_iso
.PHONY: all

override OFILES := $(shell find ./obj/ -type f -name '*.o')
override CFILES := $(shell find ./ -type f -name '*.c')
override AFILES := $(shell find ./ -type f -name '*.asm')

compile:
	@mkdir -p obj/ bin/
	@$(foreach file, $(AFILES), $(AS) $(AFLAGS) $(file) -o obj/_$(basename $(notdir $(file))).o; echo AS $(file);)
	@$(foreach file, $(CFILES), $(CC) $(CFLAGS) -c $(file) -o obj/$(basename $(notdir $(file))).o; echo CC $(file);)

	@$(CC) -Tsrc/link.ld -o bin/os.bin -ffreestanding -O2 -nostdlib $(OFILES) -lgcc
	@echo LD src/link.ld ...

make_iso:
	@mkdir -p isodir/boot/grub
	@cp bin/os.bin isodir/boot/os.bin
	@cp src/boot/grub.cfg isodir/boot/grub/grub.cfg
	@grub-mkrescue -o bin/worm-os.iso isodir 2>/dev/null


qemu: bin/worm-os.iso
	qemu-system-i386 -cdrom $^ -m 256 -debugcon stdio

clean: bin/worm-os.iso bin/ obj/ isodir/
	rm -rf $^
