package view;

import controller.ControllerTexteFichier;


public class ViewRechercheFichierTexte implements RunnableView {

    private String messageRechercheFichierTexte = "Recherche par fichier : \n" +
            "Rentrer le nom du fichier present dans la base que vous voulez comparer ou un chemin absolu : ";

    private ViewTexte viewTexte;
    private  ControllerTexteFichier controllerTexteFichier;

    ViewRechercheFichierTexte(ViewTexte viewTexte, ControllerTexteFichier controllerTexteFichier) {

        this.viewTexte = viewTexte;
        this.controllerTexteFichier = controllerTexteFichier;

    }

    @Override
    public void run() {
        init();
        System.out.print(messageRechercheFichierTexte);
        String chemin = Clavier.entrerClavierString();
        String resultat = controllerTexteFichier.rechercheParFichier(chemin);
        System.out.println(resultat);
        viewTexte.run();
    }

    private void init(){

    }
}
