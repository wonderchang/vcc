gcc -c scanner.c -o scanner.o
gcc -c main.c -o main.o
gcc main.o scanner.o -o exe.o
