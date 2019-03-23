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

    /**Recherche d'une image par sa couleur principale :
     * 1:Rouge 2:Rose 3:Bleu 4:Vert 5:Jaune 6:Orange 7:Noir 8:Blanc
     */
    public static native String rechercheParCouleur(int couleur);

    public static void main(String[] args) {
        String s = MoteurDeRecherche.rechercheParCouleur(3);
        //MoteurDeRecherche.indexationTexte();
        //System.out.println(MoteurDeRecherche.rechercheParMotCle("football"));
        //System.out.println(MoteurDeRecherche.rechercheTexteParFichier("13-Ligue_des_champions____Si_utf8.xml"));
        System.out.println("resultat : " + s);
    }

}
