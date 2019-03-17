setup:
	export JAVA_HOME=/usr/lib/jvm/java-11-openjdk-amd64

jni:
	javac -h Java_Headers/ ../../JavaWorkSpace/src/model/MoteurDeRecherche.java
	rm ../../JavaWorkSpace/src/model/MoteurDeRecherche.class

texte: ../IndexationTexte/indexationV1.c ../IndexationTexte/fileMot.c
	gcc -fPIC -shared -I"$$JAVA_HOME/include" -I"$$JAVA_HOME/include/linux" ../IndexationTexte/indexationV1.c ../IndexationTexte/fileMot.c -o Libraries/libindexation.so

#menu:
#	gcc -fPIC -I"$$JAVA_HOME/include" -I"$$JAVA_HOME/include/linux" -shared Libraries/libindexation.so ../Menu/menu.c -L"Libraries/" -libindexation -o Libraries/libmenu.so

clean:
	rm Java_Headers/*.h
	rm Libraries/*.so