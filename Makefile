CC = i686-elf-gcc
ASM = nasm

CFLAGS = -ffreestanding -nostdlib -fno-builtin -m32
ASMFLAGS = -f elf32

BUILD_DIR = build
DIST_DIR = dist

KERNEL = $(DIST_DIR)/verez86.bin
ISO = $(DIST_DIR)/verez86.iso

ASM_SOURCES = src/boot/header.asm src/boot/boot.asm
C_SOURCES = src/kernel.c src/drivers/vga.c src/drivers/io.c

ASM_OBJECTS = $(BUILD_DIR)/header.o $(BUILD_DIR)/boot.o
C_OBJECTS = $(BUILD_DIR)/kernel.o $(BUILD_DIR)/vga.o $(BUILD_DIR)/io.o

all: $(KERNEL)

$(KERNEL): $(ASM_OBJECTS) $(C_OBJECTS)
	mkdir -p $(DIST_DIR)
	i686-elf-ld -n -T linker.ld -o $(KERNEL) $(ASM_OBJECTS) $(C_OBJECTS)

$(BUILD_DIR)/header.o: src/boot/header.asm
	mkdir -p $(BUILD_DIR)
	$(ASM) $(ASMFLAGS) src/boot/header.asm -o $(BUILD_DIR)/header.o

$(BUILD_DIR)/boot.o: src/boot/boot.asm
	mkdir -p $(BUILD_DIR)
	$(ASM) $(ASMFLAGS) src/boot/boot.asm -o $(BUILD_DIR)/boot.o

$(BUILD_DIR)/kernel.o: src/kernel.c
	mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -c src/kernel.c -o $(BUILD_DIR)/kernel.o

$(BUILD_DIR)/vga.o: src/drivers/vga.c
	mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -c src/drivers/vga.c -o $(BUILD_DIR)/vga.o

$(BUILD_DIR)/io.o: src/drivers/io.c
	mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -c src/drivers/io.c -o $(BUILD_DIR)/io.o

clean:
	rm -rf $(BUILD_DIR) $(DIST_DIR)