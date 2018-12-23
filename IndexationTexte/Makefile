testIndex : fileMot.c indexationV1.c fileMot.h indexationV1.h
		gcc -c -g fileMot.c -std=c99
		gcc -c -g indexationV1.c -std=c99
		gcc -o -g testIndex.out indexationV1.o fileMot.o -std=c99 -lm

clean:
	rm -rf *.o
