package view;

import controller.ControllerRechercheNoirBlanc;

public class ViewRechercheNoirBlanc implements RunnableView {

    private String messageNB = "Quel type de recherche voulez-vous effectuer ?\n" +
            "1 - Choix d'un niveau dominant\n" +
            "2 - Recherche par fichier\n" +
            "3 - Retour\n" +
            "Choix : ";

    private ViewImage viewImage;
    private ControllerRechercheNoirBlanc controllerRechercheNoirBlanc;

    ViewRechercheNoirBlanc(ViewImage viewImage, ControllerRechercheNoirBlanc controllerRechercheNoirBlanc) {
        this.viewImage = viewImage;
        this.controllerRechercheNoirBlanc = controllerRechercheNoirBlanc;
    }

    @Override
    public void run() {
        int choix = Clavier.getIntRange(messageNB, 1, 3);

        switch (choix) {
            case 1 : //couleur dominante
                choix = -1;
                while(choix > 9 || choix < 1) {
                    System.out.print("Choisir une couleur : \n" +
                            "1 - Noir\n" +
                            "2 - Blanc\n" +
                            "Choix : ");
                    choix = Clavier.entrerClavierInt();
                }

                if(choix == 9) {
                    this.run();
                }

                System.out.println(controllerRechercheNoirBlanc.rechercheParNiveau(choix));
                this.run();
                break;
            case 2 : // par fichier
                System.out.println("Comparaison avec le fichier dans le répertoire noyau_c/IndexationImage/data/depot_image_a_compararer.");
                System.out.println(controllerRechercheNoirBlanc.rechercheImageParFichier());
                this.run();
                break;
            case 3 :
                viewImage.run();
                break;
        }
    }
}
