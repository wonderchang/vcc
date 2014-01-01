./bin/vcc test.vc
nasm -f macho64 test.asm
ld -o test test.o
