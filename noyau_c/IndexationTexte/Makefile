testIndex : fileMot.c indexationV1.c fileMot.h indexationV1.h ../Commun/Descripteurs_Textes/descripteur.c ../Commun/Descripteurs_Textes/descripteur.h
				gcc -c -g ../Commun/Descripteurs_Textes/descripteur.c -std=c99
				gcc -c -g fileMot.c -std=c99
				gcc -c -g indexationV1.c -std=c99
				gcc -o testIndex.out indexationV1.o fileMot.o descripteur.o -std=c99 -lm

clean:
	rm -rf *.o
