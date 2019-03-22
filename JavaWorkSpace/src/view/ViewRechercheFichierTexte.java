package view;

import controller.ControllerTexteFichier;

public class ViewRechercheFichierTexte implements runnableView{

    private String messageRechercheFichierTexte = "Recherche par fichier : \n" +
            "Rentrer le nom du fichier present dans la base que vous voulez comparer ou un chemin absolu : ";

    private ViewTexte viewTexte;
    private  ControllerTexteFichier controllerTexteFichier;

    public ViewRechercheFichierTexte(ViewTexte viewTexte, ControllerTexteFichier controllerTexteFichier) {

        this.viewTexte = viewTexte;
        this.controllerTexteFichier = controllerTexteFichier;

    }

    @Override
    public void run() {
        init();
        System.out.print(messageRechercheFichierTexte);
        String chemin = Clavier.entrerClavierString();
        System.out.println(controllerTexteFichier.rechercheParFichier(chemin));
        //historique
        viewTexte.run();
    }

    private void init(){

    }
}
