package controller;

import model.MoteurDeRecherche;

public class ControllerIndexation {

    public String indexationFichierTexte(String path) {
        return MoteurDeRecherche.indexationFichierTexte(path);
    }

    public String indexationFichierImage(String path) {
        return null; //todo
    }

    public String indexationFichierSon(String path) {
        return null; //todo
    }

}

