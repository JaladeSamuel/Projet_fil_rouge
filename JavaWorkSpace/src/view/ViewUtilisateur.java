package view;

public class ViewUtilisateur implements runnableView{

    private  ViewAdministrateur viewAdministrateur;
    private ViewAccueil viewAccueil;
    private ViewImage viewImage;
    private ViewTexte viewTexte;

    private boolean admin = false;
    private String accueilUtilisateur = "Sélectionner le type de fichier recherché :\n" +
            "1 - Texte\n" +
            "2 - Image\n" +
            "3 - Visualiser historique\n"+
            "4 - Retour\n" +
            "5 - Quitter\n";

    private int choix;

    public ViewUtilisateur (ViewAccueil viewAccueil) {
        this.viewAccueil = viewAccueil;
    }

    public ViewUtilisateur (ViewAdministrateur viewAdministrateur) {
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
        while (choix < 1 || choix > 5) {
            System.out.print("Choix : ");
            choix = Clavier.entrerClavierInt();
        }

        switch (choix) {
            case 1 :
                viewTexte = new ViewTexte(this);
                viewTexte.run();
                break;
            case 2 :
                viewImage = new ViewImage(this);
                viewImage.run();
                break;
            case 3 :
                System.out.println(Application.bdHistoriqueRequete.toString());
                this.run();
                break;
            case 4 :
                if(admin) {
                    this.viewAdministrateur.run();
                } else {
                    this.viewAccueil.run();
                }
                break;
            case 5 :
                Application.quitterApp();
                break;
        }
    }
}
