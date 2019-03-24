package view;

import model.MoteurDeRecherche;

public class ViewSon implements runnableView {

    private ViewUtilisateur viewUtilisateur;
    private String messageMenuSon = "Recherche par :\n" +
            "1 - Extrait\n" +
            "2 - Retour\n" +
            "3 - Quitter\n";
    private String listeExtraitsExistants = "Choisir l'extrait à utiliser pour la recherche : \n" +
            "1 - extrait1.avi\n" +
            "2 - extrait2.avi\n" +
            "3 - extrait3.avi\n";

    public ViewSon(ViewUtilisateur viewUtilisateur) {
        this.viewUtilisateur = viewUtilisateur;
    }

    @Override
    public void run() {
        int choix = Clavier.getIntRange(messageMenuSon, 1, 3);
        switch (choix) {
            case 1:
                choix = Clavier.getIntRange(listeExtraitsExistants, 1, 3);
                System.out.println(MoteurDeRecherche.rechercheSon(choix));
                // TODO : Enregistrer les résultats dans la base de données.
                break;
            case 2 :
                viewUtilisateur.run();
                break;
            case 3 :
                Application.quitterApp();
                break;
        }
    }
}
