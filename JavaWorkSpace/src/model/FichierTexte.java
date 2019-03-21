package model;

public class FichierTexte {

    private String path;
    private int similarite;
    private  String nom;


    public FichierTexte(int similarite, String nom) {
        this.nom = nom;
        this.similarite = similarite;
        this.path = "../../noyau_c/Base_de_donnees/"+nom;
    }

    public String getPath() {
        return path;
    }

    public int getSimilarite() {
        return similarite;
    }

    public String getNom() {
        return nom;
    }

    @Override
    public boolean equals(Object o) {
        return this.path.equals(((FichierTexte) o).path) && this.similarite == ((FichierTexte) o).similarite && this.nom.equals(((FichierTexte) o).nom);
    }

    @Override
    public String toString() {
        return super.toString();
    }
}
