tst_menu : menu1.c menu2.c menu3.c menu4.c menu.c menu5.c menu2.h menu3.h menu4.h menu1.h ../IndexationTexte/indexationV1.c ../IndexationTexte/indexationV1.h ../IndexationTexte/fileMot.c ../IndexationTexte/fileMot.h ../Commun/Descripteurs_Textes/descripteur.c ../Commun/Descripteurs_Textes/descripteur.h ../Comparaison/Comparaison_Texte/comparaison.c ../Comparaison/Comparaison_Texte/comparaison.h
	gcc -c -g menu.c
	gcc -c -g ../IndexationTexte/fileMot.c
	gcc -c -g ../IndexationTexte/indexationV1.c
	gcc -c -g ../Commun/Descripteurs_Textes/descripteur.c
	gcc -c -g ../Comparaison/Comparaison_Texte/comparaison.c
	gcc -o tst_menu.out menu.o fileMot.o indexationV1.o descripteur.o comparaison.o -lm
	./tst_menu.out

clean:
	rm -rf *.o
