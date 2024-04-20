main: main.c parser.c duplicates.c
	cc -Wall -Wpedantic -std=c89 main.c parser.c duplicates.c -o main

test: main
	cat testdata/valid.txt testdata/invalid.txt testdata/valid.txt > in.txt
	./main in.txt out.txt
	diff out.txt testdata/valid.txt

clean:
	@rm -f main in.txt out.txt
