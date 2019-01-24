#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include "image.h"

/*MODULE POUR LA QUANRIFICATION*/
int quantificationNoirBlanc(int nombre){
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
  int resultat[6]={0,0,0,0,0,0};
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
  
  int nb=resultat[0]*32+resultat[1]*16+resultat[2]*8+resultat[3]*4+resultat[4]*2+resultat[5]*1;
  return nb;
}

void histogrammeRGB(image m){
  int i, j;
  /* Init de chaque case a 0*/ 
  for(i=0;i<64;i++){
    m->histogramme[i] = 0;
  }
  /* Parcours de l'image */
  for(i=0;i< m->nb_lignes;i++){
    for(j=0;j< m->nb_colonnes;j++){
      m->histogramme[(m->image[i][j])] += 1;
    }
  }
}

void histogrammeNB(imageNB m){
  int i, j;
  // Init de chaque case a 0 
  for(i=0;i<4;i++){
    m->histogramme[i] = 0;
  }
  // Parcours de l'image 
  for(i=0;i< m->nb_lignes;i++){
    for(j=0;j< m->nb_colonnes;j++){
      m->histogramme[(m->image[i][j])] += 1;
    }
  }
}

//TEST

image creation_imageRGB(int nb_lignes ,int nb_colonnes){
  int i,j;
  image res;
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
        res->imageR[i][j]=0;
        res->imageG[i][j]=0;
        res->imageB[i][j]=0;
        res->image[i][j]=0;
      }        
  }
  return res ;
}

imageNB creation_imageNB(int nb_lignes ,int nb_colonnes){
  int i,j;
  imageNB res;
  res=(imageNB)malloc(sizeof(struct etImageNB));
  res->nb_lignes=nb_lignes;
  res->nb_colonnes=nb_colonnes;
  res->image=malloc(nb_lignes*sizeof(int *));
  for (i=0;i<nb_lignes;i++){
      res->image[i]=malloc(nb_colonnes*sizeof(int));
      for (j=0;j<nb_colonnes;j++){
        res->image[i][j] = 0 ;
      }        
  }
  return res ;
}

void affiche_imageRGB(image m){
  int i,j;
  for(i=0;i<m->nb_lignes;i++){
      for (j=0;j<m->nb_colonnes;j++){
        printf("%d ",m->image[i][j]);
      }
    printf("\n");
  }
}

void affiche_imageNB(imageNB m){
  int i,j;
  for(i=0;i<m->nb_lignes;i++){
      for (j=0;j<m->nb_colonnes;j++){
        printf("%d ",m->image[i][j]);
      }
    printf("\n");
  }
}

imageNB copieNB(int numeroFichier){
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
  strcat(deb,nom);
  int x,y,composante,tmp;

  FILE* fichier = NULL;
  fichier = fopen(deb, "r");
  if (fichier != NULL){
      // On peut lire et écrire dans le fichier
      fscanf(fichier,"%d %d %d",&x,&y,&composante);
      imageNB imageTMP=creation_imageNB(y,x);
      
      int i,j;
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
  strcat(deb,nom);
  int x,y,composante,tmp;

  FILE* fichier = NULL;
  fichier = fopen(deb, "r");
  if (fichier != NULL){
      // On peut lire et écrire dans le fichier
      fscanf(fichier,"%d %d %d",&x,&y,&composante);
      image imageTMP=creation_imageRGB(y,x);
      
      int i,j;
      for(i=0;i<y;i++){
        for(j=0;j<x;j++){
          fscanf(fichier,"%d",&tmp);
          imageTMP->imageR[i][j]=tmp;
        }
      }
      for(i=0;i<y;i++){
        for(j=0;j<x;j++){
          fscanf(fichier,"%d",&tmp);
          imageTMP->imageG[i][j]=tmp;
        }
      }
      for(i=0;i<y;i++){
        for(j=0;j<x;j++){
          fscanf(fichier,"%d",&tmp);
          imageTMP->imageB[i][j]=tmp;
        }
      }
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
  
  int x,y,composante,tmp;

  FILE* fichier = NULL;
  fichier = fopen(BASE_DESCRIPTEUR_IMAGE_NB, "a");
  if (fichier != NULL){
      
      // On peut lire et écrire dans le fichier
      fprintf(fichier, "%s\n",imageTMP->id);
      histogrammeNB(imageTMP);
      for(int i=0;i<4;i++){
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
  int x,y,composante,tmp;
  FILE* fichier = NULL;
  fichier = fopen(BASE_DESCRIPTEUR_IMAGE_RGB, "a");
  if (fichier != NULL){
      // On peut lire et écrire dans le fichier
      fprintf(fichier, "%s\n",imageTMP->id);
      histogrammeRGB(imageTMP);
      for(int i=0;i<64;i++){
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
  FILE* fichier = NULL;
  FILE* fichier2 = NULL;
  int x,y,composante,tmp,i,j;

  fichier = fopen("./data/liste_descripteur_imageNB.txt", "r");
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
          constructeurNB(imageTMP);
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
  FILE* fichier = NULL;
  FILE* fichier2 = NULL;
  int x,y,composante,tmp,i,j;

  fichier = fopen(LISTE_DESCRIPTEUR_IMAGE_RGB, "r");
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
          constructeurRGB(imageTMP);
          //free(imageTMP);
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
  int i,tmp;
  int somme=0;
  for(int i=0;i<4;i++){
    tmp=des1->histogramme[i] - des2->histogramme[i];
    if(tmp<0){tmp=tmp*(-1);}
    somme=somme+tmp;
  }
  return somme;  
}

int comparaisonRGB(image des1,image des2){
  int i,tmp;
  int somme=0;
  for(int i=0;i<64;i++){
    tmp=des1->histogramme[i] - des2->histogramme[i];
    if(tmp<0){tmp=tmp*(-1);}
    somme=somme+tmp;
  }
  return somme;  
}

void comparerImageAvecImageNB(){
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

  fichier = fopen("./data/listeEphemereNB.txt", "r");
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
		  fichier3 = fopen("./data/baseEphemereNB.txt", "r+");
		  if (fichier3 != NULL){
			  fprintf(fichier3, "%s\n",imageTMP->id);
			  histogrammeNB(imageTMP);
			  for(int i=0;i<4;i++){
				fprintf(fichier3,"%d %d\n",i,imageTMP->histogramme[i]);
			  }
			  fclose(fichier3);
		  }
		  else{
			  printf("Impossible d'ouvrir le fichier baseEphemereNB.txt");
		  }
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
  imageNB imageEntree=creation_imageNB(140,140);
  imageNB imageTmp=creation_imageNB(140,140);
  fichier = fopen("./data/baseEphemereNB.txt", "r");
  if(fichier != NULL){
    fscanf(fichier,"%s\n",imageEntree->id);
    for(i=0;i<4;i++){
      fscanf(fichier,"%d %d\n",&composante,&tmp);
      imageEntree->histogramme[i]=tmp;
    }
  }else{
    printf("Impossible d'ouvrir le fichier baseEphemereNB.txt");
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
    printf("Impossible d'ouvrir le fichier base_descripteur_imageNB.txt");
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
      printf("Nombre de résultat attendu supérieur au nombre de fichier présent");
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
    printf("Le ficher %s\n",tabNom[i]);
    printf("avec un comparaison à %d\n\n",tabValeur[i]);
  }
  
  sprintf(command, "rm %s", LISTE_EPHEMERE_NB);
  system(command);

  sprintf(command, "rm %s", BASE_EPHEMERE_NB);
  system(command);
}

void comparerImageAvecImageRGB(){
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
			  printf("Impossible d'ouvrir le fichier baseEphemereRGB.txt");
		  }
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
    printf("Impossible d'ouvrir le fichier baseEphemereRGB.txt");
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
    printf("Impossible d'ouvrir le fichier base_descripteur_imageNB.txt");
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
      printf("Nombre de résultat attendu supérieur au nombre de fichier présent");
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
    printf("Le ficher %s\n",tabNom[i]);
    printf("avec un comparaison à %d\n\n",tabValeur[i]);
  }
  
  sprintf(command, "rm %s", LISTE_EPHEMERE_RGB);
  system(command);

  sprintf(command, "rm %s", BASE_EPHEMERE_RGB);
  system(command);
}

//Pile dynamique
PILE init_PILE(){
  PILE p;
  p.premier=NULL;
  return p;
}
int PILE_estVide(PILE pile){
  return pile.premier==NULL;
}
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

PILE emPILE(PILE pile,int val,char * idd){
  Cell* nouvelleCase =malloc(sizeof(Cell));
  nouvelleCase->valeur=val;
  strcpy(nouvelleCase->id,idd);
  nouvelleCase->suivant=pile.premier;
  pile.premier=nouvelleCase;  
  return pile;
}


