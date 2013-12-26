gcc -c scanner.c -o scanner.o
gcc -c code-gen.c -o code-gen.o
gcc -c translator.c -o translator.o
gcc -c main.c -o main.o
gcc main.o scanner.o code-gen.o translator.o -o exe.o
