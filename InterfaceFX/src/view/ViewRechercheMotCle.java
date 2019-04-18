package view;

import controller.ControllerTexteMotCle;

public class ViewRechercheMotCle implements RunnableView {

    private ViewTexte viewTexte;
    private ControllerTexteMotCle controllerTexteMotCle;

    private String accueilViewRechercheMotCle = "Rentrer la selections de mot(s) clé(s) pour la recherche\n" +
            "1 - (+) Ajouter mot clé\n" +
            "2 - (-) Ajouter mot clé qui ne doit pas appraitre dans les resultat de la recherche\n"+
            "3 - Terminer et rechercher\n" +
            "4 - Retour\n" +
            "5 - Quitter \n";
    private int choix;

    ViewRechercheMotCle(ViewTexte viewTexte, ControllerTexteMotCle controllerTexteMotCle) {
        this.viewTexte = viewTexte;
        this.controllerTexteMotCle =controllerTexteMotCle;
    }

    public void run() {
        init();
        boolean rechercheTermine = false;

        while (!rechercheTermine) {
            choix = -1;
            while (choix < 1 || choix > 5) {
                System.out.println(accueilViewRechercheMotCle);
                System.out.print("Choix : ");
                choix = Clavier.entrerClavierInt();
            }

            switch (choix) {
                case 1:
                    System.out.print("Entrez le mot clé : ");
                    String motCle = Clavier.entrerClavierString();

                    while (controllerTexteMotCle.isMotCleNonCorrecte(motCle)) {
                        System.out.print("Ressayez : ");
                        motCle = Clavier.entrerClavierString();
                    }

                    controllerTexteMotCle.getSelectionMotARechercher().add(motCle);
                    System.out.println("Mot clé enregistré");
                    break;
                case 2:
                    if (!controllerTexteMotCle.getSelectionMotARechercher().isEmpty()) {
                        System.out.println("Entrez le mot clé non desiré : ");
                        String motcle = Clavier.entrerClavierString();

                        while (controllerTexteMotCle.isMotCleNonCorrecte(motcle)) {
                            System.out.print("Ressayez : ");
                            motcle = Clavier.entrerClavierString();
                        }

                        controllerTexteMotCle.getSelectionMotANePasRechercher().add(motcle);
                        System.out.println("Mot clé enregistré");
                    } else {
                        System.out.println("Veuillez entrer au moin 1 mot clé à rechercher");
                    }
                    break;
                case 3: //RECHERCHE
                    if (!controllerTexteMotCle.getSelectionMotARechercher().isEmpty()) {
                        System.out.println(controllerTexteMotCle.rechercheParMotCle());//recherche par mot cle
                        controllerTexteMotCle.clear(); //resultat ok on clear les listes du controleur
                    } else {
                        System.out.println("Veuillez entrer au moins 1 mot clé à rechercher");
                    }
                    break;
                case 4:
                    rechercheTermine = true;
                    viewTexte.run();
                    break;
                case 5:
                    Application.quitterApp();
                    break;
            }
        }
    }

    private void init() {
        choix = -1;
    }
}
