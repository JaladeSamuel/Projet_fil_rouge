tst_menu : menu1.c menu2.c menu3.c menu4.c menu.c menu5.c menu2.h menu3.h menu4.h menu1.h indexation_texte.o
	gcc -c menu.c
	gcc -o tst_menu.out menu.o indexation_texte.o
	./tst_menu.out

indexation_texte.o : ../IndexationTexte/fileMot.c
	gcc -c -g ../IndexationTexte/fileMot.c
	gcc -c -g ../IndexationTexte/indexationV1.c
	gcc -o 



clean:
	rm -rf *.o


mon_module_image.out: mon_module_image.o main.o
	gcc -o mon_module_image.out mon_module_image.o main.o -lm

mon_module_image.o: xiong_module_image.c 
	gcc -c xiong_module_image.c -o mon_module_image.o -lm -W -Wall -ansi -pedantic

main.o: main.c xiong_module_image.h
	gcc -o main.o -c main.c -lm -W -Wall -ansi -pedantic
