section .multiboot_header
header_start:
    dd 0xe85250d6 ; Magic number for Multiboot2
    dd 0 ; 32-bit protected mode i386

    dd header_end - header_start ; header length

    dd 0x100000000 - (0xe85250d6 + 0 + (header_end - header_start)) ; Checksum (must equal to 0)

    dw 0 ; type: end tag
    dw 0 ; flags
    dd 8 ; size of end tag

header_end: