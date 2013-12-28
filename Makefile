gcc -c ./src/scanner.c -o ./bin/scanner.o
gcc -c ./src/code-gen.c -o ./bin/code-gen.o
gcc -c ./src/translator.c -o ./bin/translator.o
gcc -c ./src/main.c -o ./bin/main.o
gcc ./bin/main.o ./bin/scanner.o ./bin/code-gen.o ./bin/translator.o -o ./bin/vcc
