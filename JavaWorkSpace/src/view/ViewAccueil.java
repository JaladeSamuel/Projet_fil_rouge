package view;

public class ViewAccueil implements runnableView{

    private ViewAdministrateur viewAdministrateur;
    private ViewUtilisateur viewUtilisateur;

    private String selectionnerUnMode = "Selectionner un mode : \n " +
            "1 - Utilisateur \n " +
            "2 - Administrateur \n";

    private int choix;

    private void init() {
        choix = -1;
    }

    public static void main(String[] arg) {
        ViewAccueil viewAccueil = new ViewAccueil();
        viewAccueil.run();
    }

    @Override
    public void run() {

        init();
        System.out.println(selectionnerUnMode);
        while (choix < 1 || choix > 2) {
            System.out.print("Type de connexion : ");
            choix = Clavier.entrerClavierInt();
        }

        if(choix == 1) {
            viewUtilisateur = new ViewUtilisateur(this);
            viewUtilisateur.run();
        } else {
            viewAdministrateur = new ViewAdministrateur(this);
        }
    }
}
