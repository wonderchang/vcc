nasm -f elf c.asm
ld -m elf_i386 -s -o c c.o
./c
