output: match.o input1.txt input2.txt
        ./match.o input1.txt input2.txt output
        cat output
        rm output

match.o: match.c coseq.h list.h string.h
        gcc match.c -o match.o -lm -O2 -ansi

clear:
        rm *o
