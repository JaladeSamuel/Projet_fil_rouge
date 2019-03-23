package view;

import controller.ControllerRechercheCouleur;

public class ViewRechercheCouleur implements runnableView {

    private String messageCouleur ="Quel type de recherche voulez-vous effectuer ?\n" +
            "1 - Choix d'une couleur dominante\n" +
            "2 - Recherche par fichier\n" +
            "3 - Retour\n" +
            "Choix : ";

    private ViewImage viewImage;
    private ControllerRechercheCouleur controllerRechercheCouleur;

    public ViewRechercheCouleur(ViewImage viewImage, ControllerRechercheCouleur controllerRechercheCouleur) {
        this.viewImage = viewImage;
        this.controllerRechercheCouleur = controllerRechercheCouleur;
    }

    @Override
    public void run() {
        int choix = -1;
        while (choix < 1 || choix > 3) {
            System.out.print(messageCouleur);
            choix = Clavier.entrerClavierInt();
            if(choix < 1 || choix > 3) {
                System.out.println("Erreur veuillez entrer un chiffre entre 1 et 3 ...");
            }
        }

        switch (choix) {
            case 1 : //couleur dominante
                choix = -1;
                while(choix > 9 || choix < 1) {
                    System.out.print("Choisir une couleur : \n" +
                            "1 - Rouge\n" +
                            "2 - Rose\n" +
                            "3 - Bleu\n" +
                            "4 - Vert\n" +
                            "5 - Jaune\n" +
                            "6 - Orange\n" +
                            "7 - Noir\n" +
                            "8 - Blanc\n" +
                            "9 - Retour\n" +
                            "Choix : ");
                    choix = Clavier.entrerClavierInt();
                }

                if(choix == 9) {
                    this.run();
                }

                System.out.println(controllerRechercheCouleur.rechercheCouleurDominanante(choix));
                this.run();
                break;
            case 2 : // par fichier
                //todo
                break;
            case 3 :
                viewImage.run();
                break;
        }



    }
}
