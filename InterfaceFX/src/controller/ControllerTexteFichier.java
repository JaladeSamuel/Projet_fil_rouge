package controller;

import model.*;
import view.Application;

import java.util.ArrayList;
import java.util.Date;
import java.util.List;

public class ControllerTexteFichier {

    private List<Fichier> listeDeFichier = new ArrayList<>();

    public String rechercheParFichier(String chemin) {

        StringBuilder resultat = new StringBuilder(MoteurDeRecherche.rechercheTexteParFichier(chemin));

        if (resultat.toString().contains("Aucun resultat n'a été trouvé.")) {
            Application.bdHistoriqueRequete.getListeRequeteTexte().add(new Requete(TypeRecherche.TEXTE_FICHIER,chemin,new Date(),"Aucun resultat n'a été trouvé"));
            return resultat.toString();
        }

        String[] aStr = resultat.toString().split(" ");
        for(String str : aStr) {
            String[] atr = str.split(":");
            listeDeFichier.add(new Fichier(Integer.parseInt(atr[1]),atr[0],TypeFichier.TEXTE));
        }

        resultat = new StringBuilder();
        for (Fichier fichier : listeDeFichier) {
            resultat.append(fichier.getNom()).append(" Similarité : ").append(fichier.getSimilarite()).append("%\n");
        }
        Application.bdHistoriqueRequete.getListeRequeteTexte().add(new Requete(TypeRecherche.TEXTE_FICHIER,chemin,new Date(),resultat.toString()));
        return resultat.toString();

    }

    private void clear() {
        listeDeFichier = new ArrayList<>();
    }
}
