
int menu3(){
	int R_par=0;
	printf("\nRecherche par :\n1 - Mot clé\n2 - Fichier\n3 - Retour\nType de Recherche : ");
	scanf("%d", &R_par);

	while(R_par!=1&&R_par!=2&&R_par!=3&&R_par!=4){
		printf("\nErreur : Saisie impossible, veuillez choisir \"1\",\"2\",\"3\" ou \"4\".\n");
		printf("\nRecherche par :\n1 - Mot clé\n2 - Fichier\n3 - Retour\nType de Recherche : ");
		scanf("%d\n", &R_par);
	}
	
	return R_par;
}
