package view;

public class ViewUtilisateur implements runnableView{

    private ViewAccueil viewAccueil;
    private ViewImage viewImage;
    private ViewTexte viewTexte;

    private String accueilUtilisateur = "Sélectionner le type de fichier recherché :\n" +
            "1 - Texte\n" +
            "2 - Image\n" +
            "3 - Retour\n" +
            "4 - Quitter\n";

    private int choix;

    public ViewUtilisateur (ViewAccueil viewAccueil) {
        this.viewAccueil = viewAccueil;
    }

    private void init() {
        choix = -1;
    }

    @Override
    public void run() {
        init();
        System.out.println(accueilUtilisateur);
        while (choix < 1 || choix > 4) {
            System.out.println("Type de fichier : ");
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
                this.viewAccueil.run();
                break;
            case 4 :
                Application.quitterApp();
                break;
        }
    }
}
