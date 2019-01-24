test: ../../Commun/Descripteurs_Textes/descripteur.h ../../Commun/Descripteurs_Textes/descripteur.c comparaison.c comparaison.h test_comparaison.c ../../IndexationTexte/indexationV1.c
	gcc -c -g ../../Commun/Descripteurs_Textes/descripteur.c
	gcc -c -g ../../IndexationTexte/indexationV1.c
	gcc -c -g comparaison.c
	gcc -c -g test_comparaison.c
	gcc -o main.out comparaison.o test_comparaison.o descripteur.o indexationV1.o
	./main.out

clean:
	rm -rf *.o