nasm -f elf d.asm
ld -m elf_i386 -s -o d d.o
./d
