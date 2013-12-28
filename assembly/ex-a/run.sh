nasm -f elf a.asm
ld -m elf_i386 -s -o a a.o
./a
