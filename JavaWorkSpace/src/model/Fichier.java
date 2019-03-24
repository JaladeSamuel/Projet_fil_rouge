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

        switch(typeFichier) {
            case TEXTE:
                this.path = "../noyau_c/Base_de_donnees/" + nom + ".xml";
                break;
            case IMAGE_RGB:
                this.path = "../noyau_c/IndexationImage/data/DATA_FIL_ROUGE_DEV/IMG_et_AUDIO/TEST_RGB" + nom + ".bmp";
                break;
            case IMAGE_NB:
                this.path = "../noyau_c/IndexationImage/data/DATA_FIL_ROUGE_DEV/IMG_et_AUDIO/TEST_NB" + nom + ".jpg";
                break;
            default:
                this.path = nom;
                break;
        }
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
        if (o instanceof Fichier) {
            return this.path.equals(((Fichier) o).path) && this.nom.equals(((Fichier) o).nom);
        } else {
            return false;
        }
    }

    @Override
    public String toString() {
        return nom + " " + similarite+"%\n";
    }
}
