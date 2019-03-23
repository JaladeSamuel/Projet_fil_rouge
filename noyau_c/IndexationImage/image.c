#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include "image.h"

/*
  Il s'agit de l'ensemble des chemins que nous utilisons dans image.c
  L'avantage est que l'on a juste besoin de modifier les variables globales pour changer les fonctions
  La BASE_EPHEMERE est utilisé pour la comparaison, elle sera créer et détruite après chaque comparaison
*/
char * BASE_DESCRIPTEUR_IMAGE_NB = "../noyau_c/IndexationImage/data/base_descripteur_imageNB.txt";
char * BASE_DESCRIPTEUR_IMAGE_RGB = "../noyau_c/IndexationImage/data/base_descripteur_imageRGB.txt";
char * BASE_EPHEMERE_NB = "../noyau_c/IndexationImage/data/baseEphemereNB.txt";
char * BASE_EPHEMERE_RGB = "../noyau_c/IndexationImage/data/baseEphemereRGB.txt";
char * LISTE_EPHEMERE_NB = "../noyau_c/IndexationImage/data/listeEphemereNB.txt";
char * LISTE_EPHEMERE_RGB = "../noyau_c/IndexationImage/data/listeEphemereRGB.txt";
char * TEST_NB_DIR_PATH = "../noyau_c/IMG_et_AUDIO/TEST_NB/";
char * TEST_RGB_DIR_PATH = "../noyau_c/IMG_et_AUDIO/TEST_RGB/";
char * LISTE_DESCRIPTEUR_IMAGE_NB = "../noyau_c/IndexationImage/data/liste_descripteur_imageNB.txt";
char * LISTE_DESCRIPTEUR_IMAGE_RGB = "../noyau_c/IndexationImage/data/liste_descripteur_imageRGB.txt";
char * DEPOT_IMAGE_A_COMPARER = "../noyau_c/IndexationImage/data/depot_image_a_compararer/";

/*MODULE POUR LA QUANRIFICATION*/


int quantificationNoirBlanc(int nombre){
  /* 
  Cette fonction va prendre en entrée un entier et retourner un entier qui sert entre 0 et 3.
  Elle sert à faire la quantification des images noir et blanc pour l'indexation.
  */
  int resultat=0;
  if(nombre-pow(2,7)>=0){
    resultat+=2; 
    if(nombre-pow(2,7)-pow(2,6)>=0){
    resultat+=1;
    }
  }
  else if(nombre-pow(2,6)>=0){
    resultat+=1;
  }
  return resultat;
}

int quantificationRGB(int nombreR,int nombreG,int nombreB){
  /* 
  Cette fonction va prendre en entrée un entier et retourner un entier qui sert entre 0 et 63.
  Elle sert à faire la quantification des images en couleur pour l'indexation.
  */
  int resultat[6]={0,0,0,0,0,0};
  //l'ensemble des conditions permet de remplir les cases du tableau "resultat". 
  if(nombreR-pow(2,7)>=0){
    resultat[0]=1;
    if(nombreR-pow(2,7)-pow(2,6)>=0){resultat[1]=1;}
  }
  else if(nombreR-pow(2,6)>=0){resultat[1]=1;}

  if(nombreG-pow(2,7)>=0){
    resultat[2]=1;
    if(nombreG-pow(2,7)-pow(2,6)>=0){resultat[3]=1;}
  }
  else if(nombreG-pow(2,6)>=0){resultat[3]=1;}

  if(nombreB-pow(2,7)>=0){
    resultat[4]=1;
    if(nombreB-pow(2,7)-pow(2,6)>=0){resultat[5]=1;}
  }
  else if(nombreB-pow(2,6)>=0){resultat[5]=1;}
  //à partir de tous les résultat obtenus dans le tableau résultat nous pourrons calculer la valeur quantifié
  int valeurQuantifier=resultat[0]*32+resultat[1]*16+resultat[2]*8+resultat[3]*4+resultat[4]*2+resultat[5]*1;
  return valeurQuantifier;
}

void histogrammeRGB(image m){
  /*
  Cette fonction prend en entrée une image rouge vert bleu et elle va modifier l'image grâce au pointeurs.
  Elle ne renvoie donc rien du tout (void). 
  Son rôle de réaliser l'histogramme de l'image donnée en paramètre.
  */
  int i, j;
  /* Initialisation de chaque case à 0*/ 
  for(i=0;i<64;i++){
    m->histogramme[i] = 0;
  }
  /* Parcours de l'image */
  for(i=0;i< m->nb_lignes;i++){
    for(j=0;j< m->nb_colonnes;j++){
      m->histogramme[(m->image[i][j])] += 1;
      //on complète directement l'histogramme de l'image
    }
  }
}

void histogrammeNB(imageNB m){
  /*
  Cette fonction prend en entrée une image noir et blanche et elle va modifier l'image grâce au pointeurs.
  Elle ne renvoie donc rien du tout (void). 
  Son rôle de réaliser l'histogramme de l'image donnée en paramètre.
  */
  int i, j;
  // Initialisation de chaque case a 0 
  for(i=0;i<4;i++){
    m->histogramme[i] = 0;
  }
  // Parcours de l'image 
  for(i=0;i< m->nb_lignes;i++){
    for(j=0;j< m->nb_colonnes;j++){
      m->histogramme[(m->image[i][j])] += 1;
      //on complète directement l'histogramme de l'image
    }
  }
}


image creation_imageRGB(int nb_lignes ,int nb_colonnes){
  /*
  Cette fonction sert à créer une image coloré. Elle prend en entrée le nombre de ligne et de colonne
  Elle renvoie une image qui sera créer. L'image au ses composantes concernant les couleurs initilisé à 0. 
  */
  int i,j; //2 variables utilisés dans les boucles for
  image res; //la nouvelle image
  res=(image)malloc(sizeof(struct etImage));
  res->nb_lignes=nb_lignes;
  res->nb_colonnes=nb_colonnes;
  res->imageR=malloc(nb_lignes*sizeof(int *));
  res->imageG=malloc(nb_lignes*sizeof(int *));
  res->imageB=malloc(nb_lignes*sizeof(int *));
  res->image=malloc(nb_lignes*sizeof(int *));
  for (i=0;i<nb_lignes;i++){
      res->image[i]=malloc(nb_colonnes*sizeof(int));
      res->imageR[i]=malloc(nb_colonnes*sizeof(int));
      res->imageG[i]=malloc(nb_colonnes*sizeof(int));
      res->imageB[i]=malloc(nb_colonnes*sizeof(int));
      for (j=0;j<nb_colonnes;j++){
        // Initialisation à 0
        res->imageR[i][j]=0;
        res->imageG[i][j]=0;
        res->imageB[i][j]=0;
        res->image[i][j]=0;
      }        
  }
  return res ;
}

imageNB creation_imageNB(int nb_lignes ,int nb_colonnes){
  /*
  Cette fonction sert à créer une image noire et blanche. Elle prend en entrée le nombre de ligne et de colonne
  Elle renvoie une image qui sera créer. L'image au ses composantes concernant les couleurs initilisé à 0. 
  */
  int i,j;//2 variables utilisés dans les boucles for
  imageNB res; //la nouvelle image
  res=(imageNB)malloc(sizeof(struct etImageNB));
  res->nb_lignes=nb_lignes;
  res->nb_colonnes=nb_colonnes;
  res->image=malloc(nb_lignes*sizeof(int *));
  for (i=0;i<nb_lignes;i++){
      res->image[i]=malloc(nb_colonnes*sizeof(int));
      for (j=0;j<nb_colonnes;j++){
        // Initialisation à 0
        res->image[i][j] = 0 ;
      }        
  }
  return res ;
}

void affiche_imageRGB(image m){
  /*
  Le rôle de cette fonction est d'affiché une image rouge vert bleu.
  Elle prend en entrée cette image et ne renvoie rien. 
  Elle est utlisé uniquement pour nos tests et pour éventuellement améliorer le code.
  */
  int i,j;
  for(i=0;i<m->nb_lignes;i++){
      for (j=0;j<m->nb_colonnes;j++){
        //affichage de la composante
        printf("%d ",m->image[i][j]);
      }
    printf("\n");
  }
}

void affiche_imageNB(imageNB m){
  /*
  Le rôle de cette fonction est d'affiché une image noir et blanche.
  Elle prend en entrée cette image et ne renvoie rien. 
  Elle est utlisé uniquement pour nos tests et pour éventuellement améliorer le code.
  */
  int i,j;
  for(i=0;i<m->nb_lignes;i++){
      for (j=0;j<m->nb_colonnes;j++){
        //affichage de la composante
        printf("%d ",m->image[i][j]);
      }
    printf("\n");
  }
}

imageNB copieNB(int numeroFichier){
  /*
  La fonction va prendre en entrée un numéro de fichier et elle va créer et renvoyé une image noire et blanche qui est la copie de l'image identifié avec le numéro
  Cette fonction sert uniquement à faire des tests, elle n'est pas utilisé. 
  Nous l'avons laissé pour faire des tests et des éventuelle amélioration dans le futur. 
  */
  char deb[]="./../IMG_et_AUDIO/TEST_NB/";
  char nom[7];
  nom[2]='.';
  nom[3]='t';
  nom[4]='x';
  nom[5]='t';
  nom[6]='\0';
  char c=numeroFichier/10+'0';
  char d=numeroFichier%10+'0';
  nom[0]=c;
  nom[1]=d;
  //recomposition du nom
  strcat(deb,nom);
  int x,y,composante,tmp;// x = nb de colonne et y = nb de ligne. tmp est une variable temporelle

  FILE* fichier = NULL;
  fichier = fopen(deb, "r");
  if (fichier != NULL){
      // On peut lire et écrire dans le fichier
      fscanf(fichier,"%d %d %d",&x,&y,&composante);
      imageNB imageTMP=creation_imageNB(y,x);
      
      int i,j;//variable utilisé pour les boucles for
      //Niveau de gris
      for(i=0;i<y;i++){
        for(j=0;j<x;j++){
          fscanf(fichier,"%d",&tmp);
          tmp=quantificationNoirBlanc(tmp);
          imageTMP->image[i][j]=tmp;
        }
      }
      //affiche_imageNB(imageTMP);
      strcpy(imageTMP->id,nom);
      fclose(fichier);
      return imageTMP;
  }
  else{
      //ouverture du fichier impossible
      printf("Impossible d'ouvrir le fichier %s",nom);
  }
}

image copieRGB(int numeroFichier){
  /*
  La fonction va prendre en entrée un numéro de fichier et elle va créer et renvoyé une image couleur qui est la copie de l'image identifié avec le numéro
  Cette fonction sert uniquement à faire des tests, elle n'est pas utilisé. 
  Nous l'avons laissé pour faire des tests et des éventuelle amélioration dans le futur. 
  */
  char deb[]="./../IMG_et_AUDIO/TEST_RGB/";
  char nom[7];
  nom[2]='.';
  nom[3]='t';
  nom[4]='x';
  nom[5]='t';
  nom[6]='\0';
  char c=numeroFichier/10+'0';
  char d=numeroFichier%10+'0';
  nom[0]=c;
  nom[1]=d;
  //recomposition du nom
  strcat(deb,nom);
  int x,y,composante,tmp;// x = nb de colonne et y = nb de ligne. tmp est une variable temporelle

  FILE* fichier = NULL;
  fichier = fopen(deb, "r");
  if (fichier != NULL){
      // On peut lire et écrire dans le fichier
      fscanf(fichier,"%d %d %d",&x,&y,&composante);
      image imageTMP=creation_imageRGB(y,x);//création d'une nouvelle image rouge vert bleu
      
      int i,j;//variable utilisé pour les boucles for
      //composante rouge
      for(i=0;i<y;i++){
        for(j=0;j<x;j++){
          fscanf(fichier,"%d",&tmp);
          imageTMP->imageR[i][j]=tmp;
        }
      }
      //composante verte
      for(i=0;i<y;i++){
        for(j=0;j<x;j++){
          fscanf(fichier,"%d",&tmp);
          imageTMP->imageG[i][j]=tmp;
        }
      }
      //composante bleu
      for(i=0;i<y;i++){
        for(j=0;j<x;j++){
          fscanf(fichier,"%d",&tmp);
          imageTMP->imageB[i][j]=tmp;
        }
      }
      // pour la quantification RGB
      for(i=0;i<y;i++){
        for(j=0;j<x;j++){
          tmp=quantificationRGB(imageTMP->imageR[i][j],imageTMP->imageG[i][j],imageTMP->imageB[i][j]);
          imageTMP->image[i][j]=tmp;
        }
      }
      //affiche_imageRGB(imageTMP);
      strcpy(imageTMP->id,nom);
      fclose(fichier);
      return imageTMP;
  }
  else{
      //ouverture du fichier impossible
      printf("Impossible d'ouvrir le fichier %s",nom);
  }
}

void constructeurNB(imageNB imageTMP){
  /*
  La fonction va prendre en entrée une image rouge verte et bleu et elle ne renvoie rien
  Elle a pour objectif de créer le descripteur d'une image donnée en entrée
  Elle va ouvrir la base des descripteurs et ajouter le nom et l'histogramme de l'image
  */
  int x,y,composante,tmp;// x = nb de colonne et y = nb de ligne. tmp est une variable temporelle

  FILE* fichier = NULL;
  fichier = fopen(BASE_DESCRIPTEUR_IMAGE_NB, "a");
  if (fichier != NULL){
      
      // On peut lire et écrire dans le fichier
      fprintf(fichier, "%s\n",imageTMP->id);
      histogrammeNB(imageTMP);
      //on a recopié l'id dans le fichier et on appelle la fonction histogramme
      for(int i=0;i<4;i++){
        //on ajoute dans le fichier les numéros de 0 à 3 et la valeur de l'histogramme associé
        fprintf(fichier,"%d %d\n",i,imageTMP->histogramme[i]);
      }
      fprintf(fichier,"\n");
      fclose(fichier);
  }
  else{
      //ouverture du fichier impossible
      printf("Impossible d'ouvrir le fichier base_descripteur_image.txt");
  }
}

void constructeurRGB(image imageTMP){
  /*
  La fonction va prendre en entrée une image rouge verte et bleu et elle ne renvoie rien
  Elle a pour objectif de créer le descripteur d'une image donnée en entrée
  Elle va ouvrir la base des descripteurs et ajouter le nom et l'histogramme de l'image
  */
  int x,y,composante,tmp;// x = nb de colonne et y = nb de ligne. tmp est une variable temporelle
  FILE* fichier = NULL;
  //ouverture de la base des descripteurs 
  fichier = fopen(BASE_DESCRIPTEUR_IMAGE_RGB, "a");
  if (fichier != NULL){
      fprintf(fichier, "%s\n",imageTMP->id);
      histogrammeRGB(imageTMP);
      //on a recopié l'id dans le fichier et on appelle la fonction histogramme
      for(int i=0;i<64;i++){
        //on ajoute dans le fichier les numéros de 0 à 64 et la valeur de l'histogramme associé
        fprintf(fichier,"%d %d\n",i,imageTMP->histogramme[i]);
      }
      fprintf(fichier,"\n");
      fclose(fichier);
  }
  else{
      //ouverture du fichier impossible
      printf("Impossible d'ouvrir le fichier base_descripteur_image.txt");
  }
}

void descripteurNB(){
  /*
  C'est la fonction principale pour créer les descripteurs. Elle ne prend aucune entrée et ne renvoie rien.
  Elle est appelée par le menu pour parcourir les images de la base d'image, elle va ensuite remplir la base de descripteur.
  Cette fonction est utilisée pour les images noires et blanches.    
  */

  //mettre les .txt dans le fichier liste_descripteur
  char command[strlen(LISTE_EPHEMERE_NB) + strlen(LISTE_DESCRIPTEUR_IMAGE_NB) + 18];

  sprintf(command, "ls %s | grep .txt > %s", TEST_NB_DIR_PATH, LISTE_DESCRIPTEUR_IMAGE_NB);
  system(command);

  sprintf(command, "echo >%s", BASE_DESCRIPTEUR_IMAGE_NB);
  system(command);

  char nom1[150];
  strcpy(nom1, TEST_NB_DIR_PATH);
  char sauveur[150];
  strcpy(sauveur, TEST_NB_DIR_PATH);
  char nom2[150]="";
  /*
  Les 2 variables fichier et fichier2 seront utilisé pour ouvrir temporairement des fichiers.
  x et y sont utilisés pour compter le nombre de ligne et de colonne.
  tmp sert de variable temporaire pour récupérer les valeurs
  i et j servent à compter dans les for
  */
  FILE* fichier = NULL;
  FILE* fichier2 = NULL;
  int x,y,composante,tmp,i,j;

  fichier = fopen(LISTE_DESCRIPTEUR_IMAGE_NB, "r");
  if (fichier != NULL){
      while(!feof(fichier)){
        strcpy(nom1,sauveur);
        //on parcours la liste des descripteurs et on va récupérer les informations pour créer une image temporaire
        fscanf(fichier,"%s\n",nom2);
        strcat(nom1,nom2);
        fichier2=fopen(nom1,"r");//ouverture de l'image
        if (fichier2 != NULL){
          fscanf(fichier2,"%d %d %d",&x,&y,&composante);
          imageNB imageTMP=creation_imageNB(y,x); //création d'une image temporaire 
          for(i=0;i<y;i++){
            for(j=0;j<x;j++){
              fscanf(fichier2,"%d",&tmp);//on va lire les entiers
              tmp=quantificationNoirBlanc(tmp); //on fait appelle à la fonction de quantification
              imageTMP->image[i][j]=tmp;
            }
          }
          //affiche_imageNB(imageTMP);
          strcpy(imageTMP->id,nom2);
          constructeurNB(imageTMP); //on fait appelle à la fonction constructeur 
        }
        else{
          printf("Impossible d'ouvrir %s\n",nom2);
        }
        fclose(fichier2);
      }
      fclose(fichier);
  }
  else{
      printf("Impossible d'ouvrir le fichier liste_descripteur_imageNB\n");
  }
}

void descripteurRGB(){
  /*
  C'est la fonction principale pour créer les descripteurs. Elle ne prend aucune entrée et ne renvoie rien.
  Elle est appelée par le menu pour parcourir les images de la base d'image, elle va ensuite remplir la base de descripteur.
  Cette fonction est utilisée pour les images colorée.    
  */

  //mettre les .txt dans le fichier liste_descripteur
  char command[strlen(LISTE_EPHEMERE_NB) + strlen(LISTE_DESCRIPTEUR_IMAGE_RGB) + 18];

  sprintf(command, "ls %s | grep .txt > %s", TEST_RGB_DIR_PATH, LISTE_DESCRIPTEUR_IMAGE_RGB);
  system(command);

  sprintf(command, "echo >%s", BASE_DESCRIPTEUR_IMAGE_RGB);
  system(command);

  char nom1[150];
  strcpy(nom1, TEST_RGB_DIR_PATH);
  char sauveur[150];
  strcpy(sauveur, TEST_RGB_DIR_PATH);
  char nom2[150]="";
  /*
  Les 2 variables fichier et fichier2 seront utilisé pour ouvrir temporairement des fichiers.
  x et y sont utilisés pour compter le nombre de ligne et de colonne.
  tmp sert de variable temporaire pour récupérer les valeurs
  i et j servent à compter dans les for
  */
  FILE* fichier = NULL;
  FILE* fichier2 = NULL;
  int x,y,composante,tmp,i,j;

  fichier = fopen(LISTE_DESCRIPTEUR_IMAGE_RGB, "r");
  if (fichier != NULL){
      while(!feof(fichier)){
        strcpy(nom1,sauveur);
        //on parcours la liste des descripteurs et on va récupérer les informations pour créer une image temporaire
        fscanf(fichier,"%s\n",nom2);
        strcat(nom1,nom2);
        fichier2=fopen(nom1,"r");//ouverture de l'image
        if (fichier2 != NULL){
          fscanf(fichier2,"%d %d %d",&x,&y,&composante);
          image imageTMP=creation_imageRGB(y,x);//création d'une image temporaire
          
          for(i=0;i<y;i++){
            for(j=0;j<x;j++){
              //on va lire les entiers et les mettres dans la composante associé (ici la rouge)
              fscanf(fichier2,"%d",&tmp);
              imageTMP->imageR[i][j]=tmp;
            }
          }
          for(i=0;i<y;i++){
            for(j=0;j<x;j++){
              //ici il s'agit de la composante verte
              fscanf(fichier2,"%d",&tmp);
              imageTMP->imageG[i][j]=tmp;
            }
          }
          for(i=0;i<y;i++){
            for(j=0;j<x;j++){
              //ici il s'agit de la composante bleu
              fscanf(fichier2,"%d",&tmp);
              imageTMP->imageB[i][j]=tmp;
            }
          }
          for(i=0;i<y;i++){
            for(j=0;j<x;j++){
              tmp=quantificationRGB(imageTMP->imageR[i][j],imageTMP->imageG[i][j],imageTMP->imageB[i][j]);//on fait appelle à la fonction de quantification
              imageTMP->image[i][j]=tmp;
            }
          }

          //affiche_imageNB(imageTMP);
          strcpy(imageTMP->id,nom2);
          constructeurRGB(imageTMP); //on fait appelle à la fonction constructeur 
          free(imageTMP); //pour libérer la mémoire 
        }
        else{
          printf("Impossible d'ouvrir %s\n",nom2);
        }
        fclose(fichier2);
      }
      fclose(fichier);
  }
  else{
      printf("Impossible d'ouvrir le fichier liste_descripteur_imageNB\n");
  }
}

//comparaison
int comparaisonNB(imageNB des1,imageNB des2){
  /*
  Fonction qui sera appelé par les fonctions de comparaison. Elle va prendre en entrée 2 images.
  Elle va parcourir les deux images et calculer les différences entre les deux histogrammes. 
  Cela lui permettra de renvoyé un entier qui correspond à un score de ressemblance.
  Plus les images se ressemblent et plus le score et petit. Fonction pour les images noires et blanches. 
  */
  int i,tmp;
  int somme=0;
  for(int i=0;i<4;i++){
    tmp=des1->histogramme[i] - des2->histogramme[i];
    //Au dessus : calcule de la différence. En dessous : l'équivalent d'une valeur obsolu.
    if(tmp<0){tmp=tmp*(-1);}
    somme=somme+tmp;
  }
  return somme;  
}

int comparaisonRGB(image des1,image des2){
  /*
  Fonction qui sera appelé par les fonctions de comparaison. Elle va prendre en entrée 2 images.
  Elle va parcourir les deux images et calculer les différences entre les deux histogrammes. 
  Cela lui permettra de renvoyé un entier qui correspond à un score de ressemblance.
  Plus les images se ressemblent et plus le score et petit. Fonction pour les images colorées. 
  */
  int i,tmp;
  int somme=0;
  for(int i=0;i<64;i++){
    tmp=des1->histogramme[i] - des2->histogramme[i];
    //Au dessus : calcule de la différence. En dessous : l'équivalent d'une valeur obsolu.
    if(tmp<0){tmp=tmp*(-1);}
    somme=somme+tmp;
  }
  return somme;  
}

void comparerImageAvecImageNB(char* string){
  
  /*
  Fonction qui parcours la liste des histogrammes noir et blancs de la base et qui la compare avec celui donnée l'image déposé
  dans le dossier. Pour cette comparaison, l'historamme de cette image est créé temporairement le temps du traitement.
  */
  //créer un descripteur du fichier entrée
  char command[strlen(LISTE_EPHEMERE_NB) + strlen(LISTE_EPHEMERE_NB) + 18];

  sprintf(command, "ls %s | grep .txt > %s", DEPOT_IMAGE_A_COMPARER, LISTE_EPHEMERE_NB);
  system(command);

  sprintf(command, "echo >%s", BASE_EPHEMERE_NB);
  system(command);

  char nom1[150];
  strcpy(nom1, DEPOT_IMAGE_A_COMPARER);
  char sauveur[150];
  strcpy(sauveur, DEPOT_IMAGE_A_COMPARER);
  char nom2[150]="";
  FILE* fichier = NULL;
  FILE* fichier2 = NULL;
  int x,y,composante,tmp,i,j;

  fichier = fopen(LISTE_EPHEMERE_NB, "r");
  if (fichier != NULL){
      while(!feof(fichier)){
        strcpy(nom1,sauveur);
        fscanf(fichier,"%s\n",nom2);
        strcat(nom1,nom2);
        fichier2=fopen(nom1,"r");//ouverture de l'image
        if (fichier2 != NULL){
          fscanf(fichier2,"%d %d %d",&x,&y,&composante);
          imageNB imageTMP=creation_imageNB(y,x);
          for(i=0;i<y;i++){
            for(j=0;j<x;j++){
              fscanf(fichier2,"%d",&tmp);
              tmp=quantificationNoirBlanc(tmp);
              imageTMP->image[i][j]=tmp;
            }
          }
          //affiche_imageNB(imageTMP);
          strcpy(imageTMP->id,nom2);
          FILE* fichier3 = NULL;
		  fichier3 = fopen(BASE_EPHEMERE_NB, "r+");
		  if (fichier3 != NULL){
			  fprintf(fichier3, "%s\n",imageTMP->id);
			  histogrammeNB(imageTMP);
			  for(int i=0;i<4;i++){
				  fprintf(fichier3,"%d %d\n",i,imageTMP->histogramme[i]);
			  }
			  fclose(fichier3);
		  }
		  else{
        strcat(string, "Impossible d'ouvrir le fichier baseEphemereNB.txt");
		  }
        }
        else{
          string += sprintf(string, "Impossible d'ouvrir %s\n", nom2);
        }
        fclose(fichier2);
      }
      fclose(fichier);
  }
  else{
      strcat(string, "Impossible d'ouvrir le fichier liste_descripteur_imageNB\n");
  }
  imageNB imageEntree=creation_imageNB(140,140);
  imageNB imageTmp=creation_imageNB(140,140);
  fichier = fopen(BASE_EPHEMERE_NB, "r");
  if(fichier != NULL){
    fscanf(fichier,"%s\n",imageEntree->id);
    for(i=0;i<4;i++){
      fscanf(fichier,"%d %d\n",&composante,&tmp);
      imageEntree->histogramme[i]=tmp;
    }
  }else{
    strcat(string, "Impossible d'ouvrir le fichier baseEphemereNB.txt");
  }
  PILE p=init_PILE();
  int resultatComp;
  fichier=fopen(BASE_DESCRIPTEUR_IMAGE_NB, "r");
  if(fichier != NULL){
    while(!feof(fichier)){
      fscanf(fichier,"%s\n",imageTmp->id);
      for(i=0;i<4;i++){
        fscanf(fichier,"%d %d\n",&composante,&tmp);
        imageTmp->histogramme[i]=tmp;
      }
      resultatComp=comparaisonNB(imageEntree,imageTmp);
      p=emPILE(p,resultatComp,imageTmp->id);
      //ici imageTmp est fini on va passer au suivant
    }
  }else{
    strcat(string, "Impossible d'ouvrir le fichier base_descripteur_imageNB.txt");
  }
  //parcourir l'ensemble des descripteurs d'image et leur appliquer la comparaison
  //empiler le résultat dans une pile d'image
  //parcourir la pile est renvoyé les plus petits
  int minim;
  PILE p2=init_PILE();
  int taillePile=taillePILE(p);
  for(i=0;i<NOMBRE_DE_RESULTAT;i++){
    minim=1000000;
    if(taillePile<NOMBRE_DE_RESULTAT){
      strcat(string, "Nombre de résultat attendu supérieur au nombre de fichier présent");
    }else{
      Cell* caseMoment = p.premier;
      while(caseMoment!=NULL){
        if(caseMoment->valeur<minim){minim=caseMoment->valeur;}
	    caseMoment=caseMoment->suivant;
	  }
      caseMoment = p.premier;
      while(caseMoment!=NULL){
        if(caseMoment->valeur==minim){
          p2=emPILE(p2,caseMoment->valeur,caseMoment->id);
		  caseMoment->valeur=1000001;
        }
	    caseMoment=caseMoment->suivant;
	  }
      
    }
  }
 
  //ParcoursPILE(p2);
  int tabValeur[NOMBRE_DE_RESULTAT];
  char tabNom[NOMBRE_DE_RESULTAT][150];
  
  i=0;
  Cell* caseMoment = p2.premier;
  while(caseMoment!=NULL){
    tabValeur[i]=caseMoment->valeur;
    strcpy(tabNom[i],caseMoment->id);
    caseMoment=caseMoment->suivant;
    i++;
  }

  for(i=NOMBRE_DE_RESULTAT-1;i>=0;i--){
    string += sprintf(string, "%s:%d ", tabNom[i], tabValeur[i]);
  }
  
  sprintf(command, "rm %s", LISTE_EPHEMERE_NB);
  system(command);

  sprintf(command, "rm %s", BASE_EPHEMERE_NB);
  system(command);

  ouvrirFichier(tabNom[NOMBRE_DE_RESULTAT-1], TEST_NB_DIR_PATH, "bmp");
}

void comparerImageAvecImageRGB(char* string){
  /*
  Fonction qui parcours la liste des histogrammes RGB de la base et qui la compare avec celui donnée l'image déposé
  dans le dossier. Pour cette comparaison, l'historamme de cette image est créé temporairement le temps du traitement.
  */
  char command[strlen(DEPOT_IMAGE_A_COMPARER) + strlen(LISTE_EPHEMERE_RGB) + 18];

  sprintf(command, "ls %s | grep .txt > %s", DEPOT_IMAGE_A_COMPARER, LISTE_EPHEMERE_RGB);
  system(command);

  sprintf(command, "echo >%s", BASE_EPHEMERE_RGB);
  system(command);

  char nom1[150];
  strcpy(nom1, DEPOT_IMAGE_A_COMPARER);
  char sauveur[150];
  strcpy(sauveur, DEPOT_IMAGE_A_COMPARER);
  char nom2[150]="";
  FILE* fichier = NULL;
  FILE* fichier2 = NULL;
  int x,y,composante,tmp,i,j;

  fichier = fopen(LISTE_EPHEMERE_RGB, "r");
  if (fichier != NULL){
      while(!feof(fichier)){
        strcpy(nom1,sauveur);
        fscanf(fichier,"%s\n",nom2);
        strcat(nom1,nom2);
        fichier2=fopen(nom1,"r");//ouverture de l'image
        if (fichier2 != NULL){
          fscanf(fichier2,"%d %d %d",&x,&y,&composante);
          image imageTMP=creation_imageRGB(y,x);
          for(i=0;i<y;i++){
            for(j=0;j<x;j++){
              fscanf(fichier2,"%d",&tmp);
              imageTMP->imageR[i][j]=tmp;
            }
          }
          for(i=0;i<y;i++){
            for(j=0;j<x;j++){
              fscanf(fichier2,"%d",&tmp);
              imageTMP->imageG[i][j]=tmp;
            }
          }
          for(i=0;i<y;i++){
            for(j=0;j<x;j++){
              fscanf(fichier2,"%d",&tmp);
              imageTMP->imageB[i][j]=tmp;
            }
          }
          for(i=0;i<y;i++){
            for(j=0;j<x;j++){
              tmp=quantificationRGB(imageTMP->imageR[i][j],imageTMP->imageG[i][j],imageTMP->imageB[i][j]);
              imageTMP->image[i][j]=tmp;
            }
          }
          
          //affiche_imageNB(imageTMP);
          strcpy(imageTMP->id,nom2);
          FILE* fichier3 = NULL;
		  fichier3 = fopen(BASE_EPHEMERE_RGB, "r+");
		  if (fichier3 != NULL){
			  fprintf(fichier3, "%s\n",imageTMP->id);
			  histogrammeRGB(imageTMP);
			  for(int i=0;i<64;i++){
				fprintf(fichier3,"%d %d\n",i,imageTMP->histogramme[i]);
			  }
			  fclose(fichier3);
		  }
		  else{
        strcat(string, "Impossible d'ouvrir le fichier baseEphemereRGB.txt");
		  }
        }
        else{
          string += sprintf(string, "mpossible d'ouvrir %s", nom2);
        }
        fclose(fichier2);
      }
      fclose(fichier);
  }
  else{
    strcat(string, "Impossible d'ouvrir le fichier liste_descripteur_imageNB\n");
  }
  image imageEntree=creation_imageRGB(y,x);
  image imageTmp=creation_imageRGB(y,x);
  fichier = fopen(BASE_EPHEMERE_RGB, "r");
  if(fichier != NULL){
    fscanf(fichier,"%s\n",imageEntree->id);
    for(i=0;i<64;i++){
      fscanf(fichier,"%d %d\n",&composante,&tmp);
      imageEntree->histogramme[i]=tmp;
    }
  }else{
    strcat(string, "Impossible d'ouvrir le fichier baseEphemereRGB.txt");
  }
  PILE p=init_PILE();
  int resultatComp;
  fichier=fopen(BASE_DESCRIPTEUR_IMAGE_RGB, "r");
  if(fichier != NULL){
    while(!feof(fichier)){
      fscanf(fichier,"%s\n",imageTmp->id);
      for(i=0;i<64;i++){
        fscanf(fichier,"%d %d\n",&composante,&tmp);
        imageTmp->histogramme[i]=tmp;
      }
      resultatComp=comparaisonRGB(imageEntree,imageTmp);  
      
      p=emPILE(p,resultatComp,imageTmp->id);
      //ici imageTmp est fini on va passer au suivant
    }
  }else{
    strcat(string, "Impossible d'ouvrir le fichier base_descripteur_imageNB.txt");
  }
  //parcourir l'ensemble des descripteurs d'image et leur appliquer la comparaison
  //empiler le résultat dans une pile d'image
  //parcourir la pile est renvoyé les plus petits
  int minim;
  PILE p2=init_PILE();
  int taillePile=taillePILE(p);
  for(i=0;i<NOMBRE_DE_RESULTAT;i++){
    minim=1000000;
    if(taillePile<NOMBRE_DE_RESULTAT){
      strcat(string, "Nombre de résultat attendu supérieur au nombre de fichier présent");
    }else{
      Cell* caseMoment = p.premier;
      while(caseMoment!=NULL){
        if(caseMoment->valeur<minim){minim=caseMoment->valeur;}
	    caseMoment=caseMoment->suivant;
	  }
      caseMoment = p.premier;
      while(caseMoment!=NULL){
        if(caseMoment->valeur==minim){
          p2=emPILE(p2,caseMoment->valeur,caseMoment->id);
		  caseMoment->valeur=1000001;
        }
	    caseMoment=caseMoment->suivant;
	  }
      
    }
  }
 
  //ParcoursPILE(p2);
  int tabValeur[NOMBRE_DE_RESULTAT];
  char tabNom[NOMBRE_DE_RESULTAT][150];
  
  i=0;
  Cell* caseMoment = p2.premier;
  while(caseMoment!=NULL){
    tabValeur[i]=caseMoment->valeur;
    strcpy(tabNom[i],caseMoment->id);
    caseMoment=caseMoment->suivant;
    i++;
  }
  for(i=NOMBRE_DE_RESULTAT-1;i>=0;i--){
    string += sprintf(string, "%s:%d ", tabNom[i], tabValeur[i]);
  }
  
  sprintf(command, "rm %s", LISTE_EPHEMERE_RGB);
  system(command);

  sprintf(command, "rm %s", BASE_EPHEMERE_RGB);
  system(command);

  ouvrirFichier(tabNom[NOMBRE_DE_RESULTAT-1], TEST_RGB_DIR_PATH, "jpg");
}

//Pile dynamique
/** Fonction qui renvoie une PILE initialisé.
 *  Elle est indispensable pour pouvoir correctement utiliser une pile.
 */
PILE init_PILE(){
  PILE p;
  p.premier=NULL;
  return p;
}

/** Fonction qui revoie si la pile donnée en paramètre est vide ou non.
 *  Revoie 1 si elle l'est, 0 sinon.
 */
int PILE_estVide(PILE pile){
  return pile.premier==NULL;
}

/** Fonction qui permet de parcourir une pile et d'afficher ses éléments. 
 *  Prends la pile à parcour en paramètre.
 */
void ParcoursPILE(PILE pile){ 
  if(pile.premier==NULL){
    printf("PILE vide");
  }else{
    Cell* caseMoment = pile.premier;
    while(caseMoment!=NULL){
      printf("%s\n",caseMoment->id);//a retirer
      printf("%d\n",caseMoment->valeur);//a retirer
      caseMoment=caseMoment->suivant;
    }
  }  
}

/** Renvoie le nombre d'éléments de la pile donnée en paramètre.
 */
int taillePILE(PILE pile){ 
  int res=0;
  if(pile.premier==NULL){
    printf("PILE vide");
  }else{
    Cell* caseMoment = pile.premier;
    while(caseMoment!=NULL){
      res++;
      caseMoment=caseMoment->suivant;
    }
  }
  return res;  
}

/** Fonction qui empile une valeur et son identifiant dans la pile.
 *  Prends une valeur de type int et une chaine de charactères pour l'id.
 */
PILE emPILE(PILE pile,int val,char * idd){
  Cell* nouvelleCase =malloc(sizeof(Cell));
  nouvelleCase->valeur=val;
  strcpy(nouvelleCase->id,idd);
  nouvelleCase->suivant=pile.premier;
  pile.premier=nouvelleCase;  
  return pile;
}

void rechercherNiveauGris(int niveau)
{
  PILE p = init_PILE();
  int i, composante, tmp, compoNivRecherche, total;
  char imageName[150];
  float resultatComp;
  
  FILE* fichier = fopen(BASE_DESCRIPTEUR_IMAGE_NB, "r");
  if (fichier != NULL)
  {
    while (!feof(fichier))
    {
      fscanf(fichier, "%s\n", imageName);

      total = 0;
      compoNivRecherche = 0;
      for (i = 0; i < 4; i++)
      {
        fscanf(fichier,"%d %d\n",&composante, &tmp);

        if (composante == niveau)
        {
          compoNivRecherche = tmp;
        }

        total += tmp;
      }

      resultatComp = (float)compoNivRecherche / (float)total * 100.0;
      p = emPILE(p, (int)resultatComp, imageName);
    }
  }
  else
  {
    printf("Impossible d'ouvrir le fichier base_descripteur_imageNB.txt");
  }

  int minim;
  PILE p2=init_PILE();
  int taillePile=taillePILE(p);
  
  for (i = 0; i < NOMBRE_DE_RESULTAT; i++)
  {
    minim=1000000;
    if (taillePile < NOMBRE_DE_RESULTAT)
    {
      printf("Nombre de résultat attendu supérieur au nombre de fichier présent");
    }
    else
    {
      Cell* caseMoment = p.premier;
      while(caseMoment!=NULL)
      {
        if(caseMoment->valeur < minim)
        {
          minim = caseMoment->valeur;
        }
	      caseMoment=caseMoment->suivant;
	    }
      caseMoment = p.premier;
      while(caseMoment!=NULL)
      {
        if (caseMoment->valeur == minim)
        {
          p2=emPILE(p2,caseMoment->valeur,caseMoment->id);
		      caseMoment->valeur=1000001;
        }
	      caseMoment=caseMoment->suivant;
	    }
    }
  }

  //ParcoursPILE(p2);
  int tabValeur[NOMBRE_DE_RESULTAT];
  char tabNom[NOMBRE_DE_RESULTAT][150];
  i=0;
  Cell* caseMoment = p2.premier;
  while(caseMoment!=NULL){
    if (i < NOMBRE_DE_RESULTAT)
    {
      tabValeur[i]=caseMoment->valeur;
      strcpy(tabNom[i],caseMoment->id);
    }
    caseMoment=caseMoment->suivant;
    i++;
  }

  for(i = 0; i < NOMBRE_DE_RESULTAT; i++){
    if (tabValeur[i] != 0)
    {
      printf(" - Le ficher %s en contient a %d %%\n", tabNom[i], tabValeur[i]);
    }
  }

  ouvrirFichier(tabNom[0], TEST_NB_DIR_PATH, "bmp");
}

void rechercherNiveauGrisStr(int niveau, char* string)
{
  PILE p = init_PILE();
  int i, composante, tmp, compoNivRecherche, total;
  char imageName[150];
  float resultatComp;
  
  FILE* fichier = fopen(BASE_DESCRIPTEUR_IMAGE_NB, "r");
  if (fichier != NULL)
  {
    while (!feof(fichier))
    {
      fscanf(fichier, "%s\n", imageName);

      total = 0;
      compoNivRecherche = 0;
      for (i = 0; i < 4; i++)
      {
        fscanf(fichier,"%d %d\n",&composante, &tmp);

        if (composante == niveau)
        {
          compoNivRecherche = tmp;
        }

        total += tmp;
      }

      resultatComp = (float)compoNivRecherche / (float)total * 100.0;
      p = emPILE(p, (int)resultatComp, imageName);
    }
  }
  else
  {
    strcat(string, "Impossible d'ouvrir le fichier base_descripteur_imageNB.txt");
  }

  int minim;
  PILE p2=init_PILE();
  int taillePile=taillePILE(p);
  
  for (i = 0; i < NOMBRE_DE_RESULTAT; i++)
  {
    minim=1000000;
    if (taillePile < NOMBRE_DE_RESULTAT)
    {
      strcat(string, "Nombre de résultat attendu supérieur au nombre de fichier présent");
    }
    else
    {
      Cell* caseMoment = p.premier;
      while(caseMoment!=NULL)
      {
        if(caseMoment->valeur < minim)
        {
          minim = caseMoment->valeur;
        }
	      caseMoment=caseMoment->suivant;
	    }
      caseMoment = p.premier;
      while(caseMoment!=NULL)
      {
        if (caseMoment->valeur == minim)
        {
          p2=emPILE(p2,caseMoment->valeur,caseMoment->id);
		      caseMoment->valeur=1000001;
        }
	      caseMoment=caseMoment->suivant;
	    }
    }
  }

  //ParcoursPILE(p2);
  int tabValeur[NOMBRE_DE_RESULTAT];
  char tabNom[NOMBRE_DE_RESULTAT][150];
  i=0;
  Cell* caseMoment = p2.premier;
  while(caseMoment!=NULL){
    if (i < NOMBRE_DE_RESULTAT)
    {
      tabValeur[i]=caseMoment->valeur;
      strcpy(tabNom[i],caseMoment->id);
    }
    caseMoment=caseMoment->suivant;
    i++;
  }

  for(i = 0; i < NOMBRE_DE_RESULTAT; i++){
    if (tabValeur[i] != 0)
    {
      strcat(string, tabNom[i]);
      strcat(string, ":");

      char percentageTemp[5];
      sprintf(percentageTemp, "%d", tabValeur[i]);
      strcat(string, percentageTemp);

      strcat(string, " ");
    }
  }

  ouvrirFichier(tabNom[0], TEST_NB_DIR_PATH, "bmp");
}

void rechercheParCouleurStr(int couleur, char* string)
{
  switch (couleur)
  {
    case 1: // ROUGE
    {
      int composantesRouge[2] = { 48, 49 };
      rechercherCouleurStr(composantesRouge, 2, string);
      break;
    }
    case 2: // ROSE
    {
      int composantesRose[2] = { 50, 51 };
      rechercherCouleurStr(composantesRose, 2, string);
      break;
    }
    case 3: // BLEU
    {
      int composantesBleu[4] = { 5, 3, 10, 1 };
      rechercherCouleurStr(composantesBleu, 4, string);
      break;
    }
    case 4: // VERT
    {
      int composantesVertes[5] = { 25, 29, 17, 12, 4 };
      rechercherCouleurStr(composantesVertes, 5, string);
      break;
    }
    case 5: // JAUNE
    {
      int composantesJaunes[6] = { 60, 61, 41, 42, 40, 43 };
      rechercherCouleurStr(composantesJaunes, 6, string);
      break;
    }
    case 6: // ORANGE
    {
      int composantesJaunes[9] = { 51, 52, 53, 61, 62, 53 };
      rechercherCouleurStr(composantesJaunes, 9, string);
      break;
    }
    case 7: // NOIR
    {
      int composantesJaunes[1] = { 0 };
      rechercherCouleurStr(composantesJaunes, 1, string);
      break;
    }
    case 8: // BLANC
    {
      int composantesJaunes[1] = { 63 };
      rechercherCouleurStr(composantesJaunes, 1, string);
      break;
    }
  }
}

void rechercherCouleur(int* tableau, int taille)
{
  float resultatComp;
  int i, composante, tmp, total, compoNivRecherche;
  char imageName[150];
  float valeurs[NOMBRE_DE_RESULTAT];
  char tabNom[NOMBRE_DE_RESULTAT][150];

  PAIRE paire;
  initPaire(&paire);

  FILE* fichier = fopen(BASE_DESCRIPTEUR_IMAGE_RGB, "r");
  if (fichier != NULL)
  {
    while (!feof(fichier))
    {
      fscanf(fichier, "%s\n", imageName);

      total = 0;
      compoNivRecherche = 0;
      for (i = 0; i < 64; i++)
      {
        fscanf(fichier,"%d %d\n",&composante, &tmp);

        if (isValeurDansTableau(composante, tableau, taille))
        {
          compoNivRecherche += tmp;
        }

        total += tmp;
      }

      resultatComp = (float)compoNivRecherche / (float)total * 100.0;
      ajouterParPaireIdValeur(&paire, imageName, resultatComp);
    }
  }
  else
  {
    printf("Impossible d'ouvrir le fichier base_descripteur_imageRGB.txt");
  }

  afficherPaire(&paire);
  ouvrirFichier(paire.ids[0], TEST_RGB_DIR_PATH, "jpg");
}

void rechercherCouleurStr(int* tableau, int taille, char* string)
{
  float resultatComp;
  int i, composante, tmp, total, compoNivRecherche;
  char imageName[150];
  float valeurs[NOMBRE_DE_RESULTAT];
  char tabNom[NOMBRE_DE_RESULTAT][150];

  PAIRE paire;
  initPaire(&paire);

  FILE* fichier = fopen(BASE_DESCRIPTEUR_IMAGE_RGB, "r");
  if (fichier != NULL)
  {
    while (!feof(fichier))
    {
      fscanf(fichier, "%s\n", imageName);

      total = 0;
      compoNivRecherche = 0;
      for (i = 0; i < 64; i++)
      {
        fscanf(fichier,"%d %d\n",&composante, &tmp);

        if (isValeurDansTableau(composante, tableau, taille))
        {
          compoNivRecherche += tmp;
        }

        total += tmp;
      }

      resultatComp = (float)compoNivRecherche / (float)total * 100.0;
      ajouterParPaireIdValeur(&paire, imageName, resultatComp);
    }
  }
  else
  {
    printf("Impossible d'ouvrir le fichier base_descripteur_imageRGB.txt");
  }

  getPaire(&paire, string);
  ouvrirFichier(paire.ids[0], TEST_RGB_DIR_PATH, "jpg");
}

void initPaire(PAIRE* paire)
{
  paire->size = 0;
  for (int i = 0; i < NOMBRE_DE_RESULTAT; i++)
  {
    paire->valeurs[i] = -1;
  }
}

void ajouterParPaireIdValeur(PAIRE* pair, char* id, float valeur)
{
  if (valeur <= 0)
  {
    return;
  }

  if (pair->size == 0)
  {
    strcpy(pair->ids[0], id);
    pair->valeurs[0] = valeur;
    pair->size++;
  }
  else
  {
    int counter = 0;
    while (counter < NOMBRE_DE_RESULTAT && pair->valeurs[counter] >= valeur && pair->valeurs[counter] != -1)
    {
      counter++;
    }

    if (counter < NOMBRE_DE_RESULTAT)
    {
      int i = 0;
      for (i = pair->size; (i >= counter && i < NOMBRE_DE_RESULTAT); i--)
      {
        strcpy(pair->ids[i + 1], pair->ids[i]);
        pair->valeurs[i + 1] = pair->valeurs[i];
      }

      strcpy(pair->ids[counter], id);
      pair->valeurs[counter] = valeur;

      if (pair->size < NOMBRE_DE_RESULTAT)
      {
        pair->size++;
      }
    }
  }
}

void afficherPaire(PAIRE* paire)
{
  if (paire->size == 0)
  {
    printf("Aucun résultat n'a été trouvé.\n");
  }
  else
  {
    for (int i = 0; i < paire->size; i++)
    {
      printf(" - %s en contient %0.1f%%\n", paire->ids[i], paire->valeurs[i]);
    }
  }
}

void getPaire(PAIRE * paire, char * paireStr)
{
  if (paire->size == 0)
  {
    strcat(paireStr, "Aucun résultat n'a été trouvé.\n");
  }
  else
  {
    for (int i = 0; i < paire->size; i++)
    {
      char percentageTemp[5];
      strcat(paireStr, paire->ids[i]);
      strcat(paireStr, ":");

      sprintf(percentageTemp, "%.0f", paire->valeurs[i]);
      strcat(paireStr, percentageTemp);

      strcat(paireStr, " ");
    }
  }
}

int isValeurDansTableau(int valeur, int *tableau, int taille)
{
  int i;
  for (i=0; i < taille; i++) {
    if (tableau[i] == valeur)
      return 1;
  }

  return 0;
}

void ouvrirFichier(char* fichier, char* locationPath, char* extension)
{
  char path[150];
  strcpy(path, locationPath);

  int dotFound = 0;
  for (int i = 0; i < strlen(fichier); i++)
  {
    if (fichier[i] == '.')
    {
      fichier[i + 1] = '\0';
      dotFound = 1;
      break;
    }
  }
  
  strcat(path, fichier);
  if (!dotFound)
  {
    strcat(path, ".");
  }
  strcat(path, extension);

  if (access(path, F_OK) != -1)
  {
    if (!fork())
    {
      execlp("eog", "eog", path, NULL);
    }
  }
}