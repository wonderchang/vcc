gcc -c ./src/scan.c -o ./bin/scan.o
gcc -c ./src/code-gen.c -o ./bin/code-gen.o
gcc -c ./src/tran.c -o ./bin/tran.o
gcc -c ./src/main.c -o ./bin/main.o
gcc ./bin/main.o ./bin/scanner.o ./bin/code-gen.o ./bin/translator.o -o ./bin/vcc
