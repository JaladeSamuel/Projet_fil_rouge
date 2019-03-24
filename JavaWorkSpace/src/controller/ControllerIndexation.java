package controller;

import model.MoteurDeRecherche;

public class ControllerIndexation {

    public String indexationFichierTexte(String path) {
        return MoteurDeRecherche.indexationFichierTexte(path);
    }

    public String indexationFichierImage(String path) {
        return "Fichier Image indexé (simulé)";
    }

    public String indexationFichierSon(String path) {
        return "Fichier Son indexé (simulé)";
    }

}

