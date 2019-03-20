package controller;

import model.FichierTexte;
import model.MoteurDeRecherche;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

public class ControllerTexteMotCle {

    private Map<String, FichierTexte> mapFichierTexte = new HashMap<>();
    private List<String> selectionMotARechercher = new ArrayList<>();
    private List<String> selectionMotANePasRechercher = new ArrayList<>();

    public Map<String, FichierTexte> getMapFichierTexte() {
        return mapFichierTexte;
    }

    public List<String> getSelectionMotARechercher() {
        return selectionMotARechercher;
    }

    public List<String> getSelectionMotANePasRechercher() {
        return selectionMotANePasRechercher;
    }

    public void clear() {
        mapFichierTexte = new HashMap<>();
        selectionMotANePasRechercher = new ArrayList<>();
        selectionMotARechercher = new ArrayList<>();
    }
}
