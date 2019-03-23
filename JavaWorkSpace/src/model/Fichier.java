package model;

public class Fichier {

    private String path;
    private int similarite;
    private String nom;
    private TypeFichier typeFichier;


    public Fichier(int similarite, String nom, TypeFichier typeFichier) {
        this.nom = nom;
        this.similarite = similarite;
        this.typeFichier = typeFichier;
        //todo bon chemin à definir
        this.path = "../noyau_c/Base_de_donnees/"+nom;
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
        return this.path.equals(((Fichier) o).path) && this.nom.equals(((Fichier) o).nom);
    }

    @Override
    public String toString() {
        return nom + " " + similarite+"%\n";
    }
}
