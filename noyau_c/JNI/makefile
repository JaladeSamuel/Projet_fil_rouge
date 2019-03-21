setup:
	export JAVA_HOME=/usr/lib/jvm/java-11-openjdk-amd64

jni:
	javac -h Java_Headers/ ../../JavaWorkSpace/src/model/MoteurDeRecherche.java
	rm ../../JavaWorkSpace/src/model/MoteurDeRecherche.class

library: ../IndexationTexte/indexationV1.c ../IndexationTexte/fileMot.c ../Comparaison/Comparaison_Texte/comparaison.c ./Libraries/jni_library.c ../Commun/Descripteurs_Textes/descripteur.c
	gcc -fPIC -shared -I"$$JAVA_HOME/include" -I"$$JAVA_HOME/include/linux" ../IndexationTexte/indexationV1.c ../IndexationTexte/fileMot.c ../Comparaison/Comparaison_Texte/comparaison.c ../Commun/Descripteurs_Textes/descripteur.c ./Libraries/jni_library.c -o Libraries/libindexation.so

clean:
	rm Java_Headers/*.h
	rm Libraries/*.so