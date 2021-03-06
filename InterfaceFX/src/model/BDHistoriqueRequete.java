package model;

import java.io.Serializable;
import java.util.ArrayList;
import java.util.List;

public class BDHistoriqueRequete implements Serializable {
    private List<Requete> listeRequeteTexte = new ArrayList<>();
    private List<Requete> listeRequeteImage = new ArrayList<>();
    private List<Requete> listeRequeteSon = new ArrayList<>();

    public String afficherHistoriqueRequeteTexte() {

        StringBuilder msg = new StringBuilder();
        if(listeRequeteTexte.isEmpty()) {
           return "Historique requetes texte vide";
        }

        for (Requete requete : listeRequeteTexte) {
            msg.append(requete.getRequete()).append("  ").append(requete.getDate().toString()).append("\n");
        }
        return msg.toString();
    }

    public List<Requete> getListeRequeteTexte() {
        return listeRequeteTexte;
    }

    public List<Requete> getListeRequeteImage() {
        return listeRequeteImage;
    }

    public List<Requete> getListeRequeteSon() {
        return listeRequeteSon;
    }

    @Override
    public String toString() {
        StringBuilder texte = new StringBuilder("Historique requetes TEXTE : \n");
        for(Requete requete : listeRequeteTexte) {
            texte.append("| ").append(requete.getDate()).append(" | Requete : ").append(requete.getRequete()).append(" | Resultat : ").append(requete.getResultat()).append("\n");
        }

        StringBuilder image = new StringBuilder("Historique requetes IMAGE : \n");
        for(Requete requete : listeRequeteImage) {
            image.append("| ").append(requete.getDate()).append(" | Requete : ").append(requete.getRequete()).append(" | Resultat : ").append(requete.getResultat()).append("\n");
        }

        StringBuilder son = new StringBuilder("Historique requetes SON : \n");
        for(Requete requete : listeRequeteSon) {
            son.append("| ").append(requete.getDate()).append(" | Requete : ").append(requete.getRequete()).append(" | Resultat : ").append(requete.getResultat()).append("\n");
        }

        return texte + "\n" + image +"\n" + son+"\n";
    }
}
