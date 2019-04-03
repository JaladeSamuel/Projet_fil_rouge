package view;

public class ViewUtilisateur implements RunnableView {

    private  ViewAdministrateur viewAdministrateur;
    private ViewAccueil viewAccueil;
    private ViewImage viewImage = new ViewImage(this);
    private ViewTexte viewTexte = new ViewTexte(this);
    private ViewSon viewSon = new ViewSon(this);
    private ViewMoteurDeRecherche viewMoteurDeRecherche = new ViewMoteurDeRecherche();

    private boolean admin = false;
    private String accueilUtilisateur = "Sélectionner le type de fichier recherché :\n" +
            "1 - Texte\n" +
            "2 - Image\n" +
            "3 - Son\n" +
            "4 - Visualiser historique\n" +
            "5 - Modifier la configuration des moteurs de recherches\n" +
            "6 - Retour\n" +
            "7 - Quitter\n";

    private int choix;

    ViewUtilisateur(ViewAccueil viewAccueil) {
        this.viewAccueil = viewAccueil;
    }

    ViewUtilisateur(ViewAdministrateur viewAdministrateur) {
        this.viewAdministrateur = viewAdministrateur;
        admin = true;
    }

    private void init() {
        choix = -1;
    }

    @Override
    public void run() {
        init();
        System.out.println(accueilUtilisateur);
        while (choix < 1 || choix > 7) {
            System.out.print("Choix : ");
            choix = Clavier.entrerClavierInt();
        }

        switch (choix) {
            case 1 :
                viewTexte.run();
                break;
            case 2 :
                viewImage.run();
                break;
            case 3 :
                viewSon.run();
                break;
            case 4 :
                System.out.println(Application.bdHistoriqueRequete.toString());
                this.run();
                break;
            case 5 :
                viewMoteurDeRecherche.run();
                this.run();
                break;
            case 6 :
                if(admin) {
                    this.viewAdministrateur.run();
                } else {
                    this.viewAccueil.run();
                }
                break;
            case 7 :
                Application.quitterApp();
                break;
        }
    }
}
