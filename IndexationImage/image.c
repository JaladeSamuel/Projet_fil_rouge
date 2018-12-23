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
  char deb[]="/home/thomas/Documents/TP_C/PFR/data/DATA_FIL_ROUGE_DEV/IMG_et_AUDIO/TEST_NB/";
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
  char deb[]="/home/thomas/Documents/TP_C/PFR/data/DATA_FIL_ROUGE_DEV/IMG_et_AUDIO/TEST_RGB/";
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
  fichier = fopen("./data/base_descripteur_imageNB.txt", "a");
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
  fichier = fopen("/home/thomas/Documents/TP_C/PFR/data/base_descripteur_imageRGB.txt", "a");
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
  system("ls data/DATA_FIL_ROUGE_DEV/IMG_et_AUDIO/TEST_NB/ | grep .txt > data/liste_descripteur_imageNB.txt");
  system("echo "">./data/base_descripteur_imageNB.txt");
  char nom1[150]="./data/DATA_FIL_ROUGE_DEV/IMG_et_AUDIO/TEST_NB/";
  char sauveur[150]="./data/DATA_FIL_ROUGE_DEV/IMG_et_AUDIO/TEST_NB/";
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
  system("ls data/DATA_FIL_ROUGE_DEV/IMG_et_AUDIO/TEST_RGB/ | grep .txt > data/liste_descripteur_imageRGB.txt");
  system("echo "">./data/base_descripteur_imageRGB.txt");
  char nom1[150]="./data/DATA_FIL_ROUGE_DEV/IMG_et_AUDIO/TEST_RGB/";
  char sauveur[150]="./data/DATA_FIL_ROUGE_DEV/IMG_et_AUDIO/TEST_RGB/";
  char nom2[150]="";
  FILE* fichier = NULL;
  FILE* fichier2 = NULL;
  int x,y,composante,tmp,i,j;

  fichier = fopen("./data/liste_descripteur_imageRGB.txt", "r");
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


