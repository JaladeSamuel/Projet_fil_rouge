package model;

import java.util.ArrayList;
import java.util.List;

public class BDHistoriqueRequete {
    private List<Requete> listeRequeteTexte = new ArrayList<>();
    private List<Requete> listeRequeteImage = new ArrayList<>();

    public List<Requete> getListeRequeteTexte() {
        return listeRequeteTexte;
    }

    public List<Requete> getListeRequeteImage() {
        return listeRequeteImage;
    }

    public List<Requete> getListeRequeteSon() {
        return listeRequeteSon;
    }

    private List<Requete> listeRequeteSon = new ArrayList<>();
}
