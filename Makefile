gcc -c ./src/main.c -o ./bin/main.o
gcc -c ./src/scan.c -o ./bin/scan.o
gcc -c ./src/tran.c -o ./bin/tran.o
gcc -c ./src/util.c -o ./bin/util.o
gcc -c ./src/act-rou.c -o ./bin/act-rou.o
gcc -c ./src/sym-tab.c -o ./bin/sym-tab.o
gcc -c ./src/err-han.c -o ./bin/err-han.o
gcc -c ./src/dbg-aid.c -o ./bin/dbg-aid.o
gcc -c ./src/cod-gen.c -o ./bin/cod-gen.o
gcc ./bin/main.o ./bin/scan.o ./bin/tran.o ./bin/util.o ./bin/act-rou.o ./bin/sym-tab.o ./bin/err-han.o ./bin/dbg-aid.o ./bin/cod-gen.o -o ./vcc
