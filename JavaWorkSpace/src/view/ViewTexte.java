package view;

import controller.ControllerTexteMotCle;

public class ViewTexte implements runnableView {

    private ViewUtilisateur viewUtilisateur;
    private ViewRechercheMotCle viewRechercheMotCle;


    private String accueilViewTexte = "Recherche par :\n" +
            "1 - Mot clé\n" +
            "2 - Fichier\n" +
            "3 - Retour\n" +
            "4 - Quitter\n";

    private int choix;

    ViewTexte(ViewUtilisateur viewUtilisateur) {
        this.viewUtilisateur = viewUtilisateur;
    }

    private void init() {
        choix = -1;
    }

    @Override
    public void run() {
        init();
        System.out.println(accueilViewTexte);
        while (choix < 1 || choix > 4) {
            System.out.print("Type de recherche : ");
            choix = Clavier.entrerClavierInt();
        }

        switch (choix) {
            case 1 :
                //mot clé
                viewRechercheMotCle = new ViewRechercheMotCle(this, new ControllerTexteMotCle());
                viewRechercheMotCle.run();
                break;
            case 2 :
                //fichier
                break;
            case 3 :
                viewUtilisateur.run();
                break;
            case 4 :
                System.exit(1);

        }
    }
}
