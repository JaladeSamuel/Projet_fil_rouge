package model;

public class MoteurDeRecherche {

    static {
        try {
            System.loadLibrary("indexation");
        }
        catch(UnsatisfiedLinkError e) {
            System.out.println("Erreur de chargement des librairies :\n" + e);
            System.exit(1);
        }
    }

    public static native void indexationTexte();

    public static void main(String args[]) {
        MoteurDeRecherche.indexationTexte();
    }

}
