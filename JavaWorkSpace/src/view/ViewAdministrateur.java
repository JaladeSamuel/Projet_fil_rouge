package view;

public class ViewAdministrateur implements runnableView {

    private ViewAccueil viewAccueil;
    private ViewImage viewImage;
    private ViewTexte viewTexte;
    private ViewImage viewSon;
    private ViewDescripteur viewDescripteur;
    private ViewUtilisateur viewUtilisateur;

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
        String tentative;
        String motDePasse = "123upssitech";
        do {
            System.out.println("Mot de passe : ");
            tentative = Clavier.entrerClavierString();
        } while (!tentative.equals(motDePasse));
    }

    @Override
    public void run() {
        init();

        while (choix < 1 || choix > 6) {
            System.out.println(accueilAdministrateur);
            choix = Clavier.entrerClavierInt();
            if(choix < 1 || choix > 6){
                System.out.println("Erreur : Saisie impossible, veuillez choisir \"1\",\"2\",\"3\",\"4\",\"5\" ou \"6\".\n");
            }
        }
        switch (choix) {
            case 1 : //Lancer une recherche
                //TODO
                break;
            case 2 : //Accéder aux descripteurs
                //TODO
                break;
            case 3 : //Modifier les configurations
                //TODO
                break;
            case 4 ://Retour
                this.viewAccueil.run();
                break;
            case 5 : //Quitter
                Application.quitterApp();
                break;
        }
    }
}
