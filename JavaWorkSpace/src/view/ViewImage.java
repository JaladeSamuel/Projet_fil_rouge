package view;

//import controller.truc;

public class ViewImage implements runnableView {

    private ViewUtilisateur viewUtilisateur;
    //private ViewRechercheCouleur viewRechercheCouleur;
    //private ViewRechercheNoirBlanc rechercheNoirBlanc;

    private String accueilViewSon = "Sélectionner un type d'image :\n"+
            "1 - Noir et Blanc\n"+
            "2 - Couleur\n"+
            "3 - Retour\n"+
            "4 - Quitter\n"+
            "Type de recherche : ";
    private int choix;

    public ViewImage(ViewUtilisateur viewUtilisateur) {
        this.viewUtilisateur = viewUtilisateur;
    }
    private void init() {
        choix = -1;
    }

    @Override
    public void run() {
        init();
        do {
            System.out.println(accueilViewSon);
            System.out.println("\nErreur : Saisie impossible, veuillez choisir \"1\",\"2\" ou \"3\".\n");
        } while (choix < 1 || choix > 4);
        switch (choix) {
            case 1:
                //noir et blanc
                //viewRechercheCouleur = new ViewRechercheCouleur(this.new ControllerRechercheCouleur());
                //viewRechercherCouleur.run();
                break;
            case 2:
                //couleur
                //viewRechercheNoirBlanc = new ViewRechercheNoirBlanc(this.new ControllerRechercheNoirBlanc());
                //viewRechercherNoirBlanc.run();
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
