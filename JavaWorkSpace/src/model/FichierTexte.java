package model;

public class FichierTexte {

    private String motRecherche;
    private int nbOccurenceMot;
    private String path;


    public FichierTexte(String motRecherche, int nbOccurence, String nomChemin) {
        this.motRecherche = motRecherche;
        this.nbOccurenceMot = nbOccurence;
        this.path = nomChemin;
    }


}
