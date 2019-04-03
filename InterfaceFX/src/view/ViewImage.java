package view;


import controller.ControllerRechercheCouleur;
import controller.ControllerRechercheNoirBlanc;

public class ViewImage implements RunnableView {

    private ViewUtilisateur viewUtilisateur;
    private ViewRechercheCouleur viewRechercheCouleur;
    private ViewRechercheNoirBlanc viewRechercheNoirBlanc;

    private String accueilViewSon = "Sélectionner un type d'image :\n"+
            "1 - Noir et Blanc\n"+
            "2 - Couleur\n"+
            "3 - Retour\n"+
            "4 - Quitter\n"+
            "Type de recherche : ";
    private int choix;

    ViewImage(ViewUtilisateur viewUtilisateur) {
        this.viewUtilisateur = viewUtilisateur;
    }
    private void init() {
        choix = -1;
    }

    @Override
    public void run() {
        init();
        do {
            System.out.print(accueilViewSon);
            choix = Clavier.entrerClavierInt();
        } while (choix < 1 || choix > 4);
        switch (choix) {
            case 1:
                //noir et blanc
                viewRechercheNoirBlanc = new ViewRechercheNoirBlanc(this,new ControllerRechercheNoirBlanc());
                viewRechercheNoirBlanc.run();
                break;
            case 2:
                //couleur
                viewRechercheCouleur = new ViewRechercheCouleur(this,new ControllerRechercheCouleur());
                viewRechercheCouleur.run();
                break;
            case 3:
                //retour
                viewUtilisateur.run();
                break;
            case 4:
                Application.quitterApp();
                break;
        }
    }
}
