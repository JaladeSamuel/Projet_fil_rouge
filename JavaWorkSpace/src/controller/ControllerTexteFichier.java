package controller;

import model.*;

import java.util.ArrayList;
import java.util.Date;
import java.util.List;

public class ControllerTexteFichier {

    private BDHistoriqueRequete bdHistoriqueRequete = new BDHistoriqueRequete();
    private List<FichierTexte> listeDeFichierTexte = new ArrayList<>();

    public String rechercheParFichier(String chemin) {

        StringBuilder resultat = new StringBuilder(MoteurDeRecherche.rechercheTexteParFichier(chemin));
        System.out.println("RESULTAT BRUT "+resultat);
        if (resultat.toString().contains("Aucun resultat n'a été trouvé.")) {
            return resultat.toString();
        }

        String[] aStr = resultat.toString().split(" ");
        for(String str : aStr) {
            String[] atr = str.split(":");
            listeDeFichierTexte.add(new FichierTexte(Integer.parseInt(atr[1]),atr[0]));
        }

        bdHistoriqueRequete.getListeRequeteTexte().add(new Requete(TypeRecherche.TEXTE_FICHIER,chemin,new Date()));

        resultat = new StringBuilder();
        for (FichierTexte fichier : listeDeFichierTexte) {
            resultat.append(fichier.getNom()).append(" Similarité : ").append(fichier.getSimilarite()).append("%\n");
        }
        return resultat.toString();

    }

    private void clear() {
        listeDeFichierTexte = new ArrayList<>();
    }
}
