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

    public static native String rechercheParMotCle(String motCle);

    public static native String rechercheTexteParFichier(String chemin);

    public static void main(String[] args) {
        //MoteurDeRecherche.indexationTexte();
        //System.out.println(MoteurDeRecherche.rechercheParMotCle("football"));
        //System.out.println(MoteurDeRecherche.rechercheTexteParFichier("15-Capturer_et_emprisonner_le_CO_utf8.xml"));
        System.out.println(rechercheTexteParFichier("13-Ligue_des_champions____Si_utf8.xml"));
    }

}
