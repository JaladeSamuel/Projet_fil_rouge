tst_menu : menu1.c menu2.c menu3.c menu4.c menu.c menu5.c menu2.h menu3.h menu4.h menu1.h ../IndexationTexte/indexationV1.c ../IndexationTexte/indexationV1.h ../IndexationTexte/fileMot.c ../IndexationTexte/fileMot.h
	gcc -c menu.c
	gcc -c ../IndexationTexte/fileMot.c
	gcc -c ../IndexationTexte/indexationV1.c
	gcc -o tst_menu.out menu.o ../IndexationTexte/fileMot.o ../IndexationTexte/indexationV1.c -lm
	./tst_menu.out


clean:
	rm -rf *.o
