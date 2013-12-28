nasm -f elf first.asm
ld -m elf_i386 -s -o first first.o
./first
