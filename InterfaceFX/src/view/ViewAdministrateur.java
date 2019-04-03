package view;

import controller.ControllerIndexation;

import java.awt.*;
import java.io.File;
import java.io.IOException;

public class ViewAdministrateur implements RunnableView {

    private ViewAccueil viewAccueil;
    private ViewUtilisateur viewUtilisateur;
    private ControllerIndexation controllerIndexation = new ControllerIndexation();

    private boolean mdpTrue = false;
    private String accueilAdministrateur = "Sélectionner une action :\n" +
            "1 - Lancer une recherche\n"+
            "2 - Accéder aux descripteurs\n"+
            "3 - Lancer une indexation\n"+
            "4 - Modifier les configurations\n"+
            "5 - Retour\n"+
            "6 - Quitter\n"+
            "Choix :";

    private int choix;

    ViewAdministrateur(ViewAccueil viewAccueil) {
        this.viewAccueil = viewAccueil;
    }

    private void init() {
        choix = -1;
        if(!mdpTrue) {
            String tentative;
            String motDePasse = "123upssitech";
            do {
                System.out.println("Mot de passe : ");
                tentative = Clavier.entrerClavierString();
            } while (!tentative.equals(motDePasse));
        }
        mdpTrue = true;
    }

    @Override
    public void run() {
        init();

        while (choix < 1 || choix > 6) {
            System.out.print(accueilAdministrateur);
            choix = Clavier.entrerClavierInt();
            if(choix < 1 || choix > 6){
                System.out.println("Erreur : Saisie impossible, veuillez choisir \"1\",\"2\",\"3\",\"4\",\"5\" ou \"6\".\n");
            }
        }
        switch (choix) {
            case 1 : //Lancer une recherche
                viewUtilisateur = new ViewUtilisateur(this);
                viewUtilisateur.run();
                break;
            case 2 : //Accéder aux descripteurs
                choix = -1;
                while (choix > 3 || choix < 1) {
                    System.out.println("1 - Descripteurs texte\n" +
                            "2 - Descripteurs image (RGB et Noir et Blanc)\n" +
                            "3 - Descripteurs son");
                    System.out.print("Choix : ");
                    choix = Clavier.entrerClavierInt();
                }
                switch (choix) {
                    case 1 :
                        try {
                            Desktop.getDesktop().open(new File("../noyau_c/Commun/descripteur_base_texte.txt"));
                        } catch (IOException e) {
                            e.printStackTrace();
                        }
                        break;
                    case 2 :
                        try {
                            Desktop.getDesktop().open(new File("../noyau_c/IndexationImage/data/base_descripteur_imageNB.txt"));
                            Desktop.getDesktop().open(new File("../noyau_c/IndexationImage/data/base_descripteur_imageRGB.txt"));
                        } catch (IOException e) {
                            e.printStackTrace();
                        }
                        break;
                    case 3 :
                        try {
                            Desktop.getDesktop().open(new File("../noyau_c/IndexationImage/data/base_descripteur_audio.txt"));
                        } catch (IOException e) {
                            e.printStackTrace();
                        }
                        break;
                }
                this.run();
                break;
            case 3 : //Lancer une indexation
                int choix = -1;
                while (choix < 1 || choix > 3) {
                    System.out.println("Type d'indexation : \n" +
                            "1 - Texte \n" +
                            "2 - Image \n" +
                            "3 - Son\n" +
                            "Choix : ");
                    choix = Clavier.entrerClavierInt();
                }
                System.out.print("Entrez le chemin absolu du fichier que vous voulez indexer : ");
                String chemin = Clavier.entrerClavierString();
                switch (choix) {
                    case 1 :
                        System.out.println(controllerIndexation.indexationFichierTexte(chemin));
                        this.run();
                        break;
                    case 2 :
                        System.out.println(controllerIndexation.indexationFichierImage(chemin));
                        this.run();
                        break;
                    case 3 :
                        System.out.println(controllerIndexation.indexationFichierSon(chemin));
                        this.run();
                        break;

                }

                break;
            case 4 : //Modifier les configurations
                choix = -1;
                while (choix > 4 || choix < 1) {
                    System.out.println("1 - Configuration générale\n" +
                            "2 - Configuration texte)\n" +
                            "3 - Configuration image\n" +
                            "4 - Configuration son");
                    System.out.print("Choix : ");
                    choix = Clavier.entrerClavierInt();
                    switch (choix) {
                        case 1 :
                            try {
                                Desktop.getDesktop().open(new File("../noyau_c/Config/config.txt"));
                            } catch (IOException e) {
                                e.printStackTrace();
                            }
                            break;
                        case 2 :
                            try {
                                Desktop.getDesktop().open(new File("../noyau_c/Config/config_texte.txt"));
                            } catch (IOException e) {
                                e.printStackTrace();
                            }
                            break;
                        case 3 :
                            try {
                                Desktop.getDesktop().open(new File("../noyau_c/Config/config_image.txt"));
                            } catch (IOException e) {
                                e.printStackTrace();
                            }
                            break;
                        case 4 :
                            try {
                                Desktop.getDesktop().open(new File("../noyau_c/Config/config_son.txt"));
                            } catch (IOException e) {
                                e.printStackTrace();
                            }
                            break;
                    }
                    this.run();
                }
                break;
            case 5 ://Retour
                this.mdpTrue = false;
                this.viewAccueil.run();
                break;
            case 6 : //Quitter
                Application.quitterApp();
                break;
        }
    }
}
