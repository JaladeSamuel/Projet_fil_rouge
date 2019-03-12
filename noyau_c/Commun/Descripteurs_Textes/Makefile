test_descr: descripteur.c descripteur.h test_descripteurs.c
	gcc -c -g descripteur.c
	gcc -c -g test_descripteurs.c
	gcc -o main.out descripteur.o test_descripteurs.o
	./main.out

clean: 
	rm -rf *.o