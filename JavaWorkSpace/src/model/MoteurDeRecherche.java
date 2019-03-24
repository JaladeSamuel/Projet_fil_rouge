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

    public static void indexationImage() {
        //todo ...
    }

    public static void indexationSon() {
        //todo ...
    }

    public static native String indexationFichierTexte(String chemin);

    public static native String rechercheParMotCle(String motCle);

    public static native String rechercheTexteParFichier(String chemin);

    /**Recherche d'une image par sa couleur principale.
     * @param couleur 1:Rouge, 2:Rose, 3:Bleu, 4:Vert, 5:Jaune, 6:Orange, 7:Noir ou 8:Blanc
     */
    public static native String rechercheParCouleur(int couleur);

    /**Recherche d'une image en noir et blanc par son niveau.
     * @param niveau 0:noir 1:blanc
     */
    public static native String rechercheNoirEtBlanc(int niveau);

    /**Recherche d'une image couleur en comparaison avec une autre image.
     * Cette image doit être dans le dossier de recherche d'image.
     * @return Liste des résultats sous la forme : resultat1:distance resultat2:distance ...
     */
    public static native String rechercheImageRGBParFichier();

    /**Recherche d'une image noire et blanche en comparaison avec une autre image.
     * Cette image doit être dans le dossier de recherche d'image.
     * @return Liste des résultats sous la forme : resultat1:distance resultat2:distance ...
     */
    public static native String rechercheImageNBParFichier();

    public static String rechercheSon(int extrait) {
        switch (extrait) {
            case 1:
                return "son1.avi son4.avi son3.avi";
            case 2:
                return "son2.avi son7.avi son2.avi son4.avi";
            case 3:
                return "son7.avi son4.avi";
            default:
                return "Cet extrait n'est pas connu dans la base.";
        }
    }

    public static void main(String[] args) {
        String s = MoteurDeRecherche.rechercheImageNBParFichier();
        //rechercheParCouleur(3);
        //indexationTexte();
        //rechercheParMotCle("football");
        //rechercheTexteParFichier("13-Ligue_des_champions____Si_utf8.xml");
        System.out.println("resultat : " + s);
    }

}
